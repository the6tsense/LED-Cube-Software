#include "font.h"

#define DEBUG_FONTREADER

int Font::s_fontAmount = 0;

Font::Font() :
    m_next(nullptr)
{
    m_font = new Letter();
    s_fontAmount++;
}

Font::~Font()
{
    Letter* currentLetter = m_font;
    Letter* nextLetter = m_font;
    while(nextLetter != nullptr)
    {
        currentLetter = nextLetter;
        nextLetter = currentLetter->next();
        delete(currentLetter);
    }
    s_fontAmount--;
}

Letter* Font::getLetter(int letter)
{
    Letter* currentLetter = m_font;
    while(currentLetter != nullptr)
    {
        if(currentLetter->getLetterIndex() == letter)
        {
            return currentLetter;
        }
        currentLetter = currentLetter->next();
    }
    std::cout << "Letter not found." << std::endl;
    return m_font;
}

int Font::readFont(QString filepath)
{
    char buf[256];
    std::vector<bool>* letter;
    int letterIndex = 0;
    int firstIndex = 0;
    int firstStage = 0;
    int secondStage = 0;
    int thirdStage = 0;
    int letterAmount = 0;
    int rowCheck = 0;
    int width = 0;
    int height = 0;
    int letterNum = 0;
    Letter* currentLetter = m_font;

    std::fstream fs(filepath.toStdString(), std::fstream::in);

    //open file
    if(fs.is_open())
    {
        //read line and convert to QString
        fs.getline(buf, 256);
        QString st = QString(buf);

        //check for enf of file
        while(!fs.eof())
        {
            //delete all whitespaces
            st = st.simplified();
            st.replace(" ", "");

            //check for compliance with xml
            if(st.at(0) == '<')
            {
                //pre sort by first letter
                switch(st.at(1).toLatin1())
                {
                    //closing xml statement
                    case '/':
                        //presort by first letter
                        switch(st.at(2).toLatin1())
                        {
                            case 'b':
                                //bitmatrix was closed
                                if(st.contains("bitmatrix"))
                                {
                                    //step out of third stage
                                    thirdStage = 0;
                                }
                                //throw error
                                else
                                {
                                    return 1;
                                }
                                break;

                            case 'l':
                                //letters was closed
                                if(st.contains("letters"))
                                {
                                    //step out of first stage
                                    firstStage = 0;
                                }
                                //letter was closed
                                else if(st.contains("letter"))
                                {
                                    //step out of second stage
                                    secondStage = 0;

                                    //create new letter
                                    currentLetter->setNext(new Letter(width,
                                                                     height,
                                                                     letterNum,
                                                                     letter)
                                                           );

                                    #ifdef DEBUG_FONTREADER
                                    std::cout
                                            << currentLetter->toString().toStdString()
                                            << std::endl;
                                    #endif

                                    //go to new letter
                                    currentLetter = currentLetter->next();

                                    //increase amount of letters
                                    letterAmount++;

                                    //reset rows
                                    rowCheck = 0;
                                }
                                //throw error
                                else
                                {
                                    return 1;
                                }
                                break;

                            case 's':
                                //size was closed
                                if(st.contains("size"))
                                {
                                    //check whether width and height has been found
                                    if(width < 1 || height < 1)
                                    {
                                        //print error
                                        std::cout
                                                << "Width and/or height of font not found."
                                                << std::endl;
                                        return 2;
                                    }

                                    //leave first stage
                                    firstStage = 0;
                                }
                                //throw error
                                else
                                {
                                    return 1;
                                }
                                break;
                        }
                        break;

                    case 'b':
                        //check stage
                        if(secondStage)
                        {
                            //begin of bitmatrix
                            if(st.contains("bitmatrix"))
                            {
                                //set third stage
                                thirdStage = 1;
                            }
                            //throw error
                            else
                            {
                                return 3;
                            }
                        }
                        //throw error
                        else
                        {
                            return 1;
                        }
                        break;

                    case 'h':
                        //check stage
                        if(firstStage == 1)
                        {
                            //begin of height
                            if(st.contains("height"))
                            {
                                //get height of font
                                firstIndex = st.indexOf('>');
                                firstIndex++;
                                QStringRef sub(&st,
                                               firstIndex,
                                               st.indexOf('<', firstIndex) - firstIndex);
                                height = sub.toInt();
                            }
                            //throw error
                            else
                            {
                                return 3;
                            }
                        }
                        //throw error
                        else
                        {
                            return 1;
                        }
                        break;

                    case 'i':
                        //check stage
                        if(secondStage)
                        {
                            //begin of index
                            if(st.contains("index"))
                            {
                                //get index of letter
                                firstIndex = st.indexOf('>');
                                firstIndex++;
                                QStringRef sub(&st,
                                               firstIndex,
                                               st.indexOf('<', firstIndex) - firstIndex);
                                letterNum = sub.toInt();
                            }
                            //throw error
                            else
                            {
                                return 3;
                            }
                        }
                        //throw error
                        else
                        {
                            return 1;
                        }
                        break;

                    case 'l':
                        //begin of letters
                        if(st.contains("letters"))
                        {
                            //set first stage
                            firstStage = 2;
                        }
                        //check stage
                        else if(firstStage == 2)
                        {
                            //begin of letter
                            if(st.contains("letter"))
                            {
                                //set second stage
                                secondStage = 1;

                                //create new bool array for letter
                                letter = new std::vector<bool>(width * height);
                                letterIndex = 0;
                            }
                            //throw error
                            else
                            {
                                return 3;
                            }
                        }
                        //throw error
                        else
                        {
                            return 1;
                        }
                        break;

                    case 'r':
                        //check stage
                        if(thirdStage)
                        {
                            //begin of row
                            if(st.contains("row"))
                            {
                                //check row count for too many rows
                                if(rowCheck >= height)
                                {
                                    std::cout
                                            << "Found too many rows"
                                            << std::endl;
                                    return 4;
                                }

                                firstIndex = st.indexOf('>');
                                firstIndex++;
                                int size = st.indexOf('<', firstIndex) - firstIndex;

                                if(size != width)
                                {
                                    std::cout
                                            << "Not enough bits in bitmatrixrow."
                                            << std::endl;
                                    break;
                                }

                                QStringRef sub(&st, firstIndex, size);

                                for(int i = 0; i < size; i++)
                                {
                                    if(sub.at(i).toLatin1() == '1')
                                    {
                                        letter->operator[] (letterIndex++) = true;
                                    }
                                    else if(sub.at(i).toLatin1() == '0')
                                    {
                                        letter->operator[] (letterIndex++) = false;
                                    }
                                    else
                                    {
                                        std::cout
                                                << "Unknown description in bitmatrix found."
                                                << std::endl;
                                    }
                                }
                                rowCheck++;
                            }
                        }
                        else
                        {
                            std::cout << "unknown xml command: " << st.toStdString() << std::endl;
                        }
                        break;

                    case 's':
                        if(st.contains("size"))
                        {
                            firstStage = 1;
                        }
                        else
                        {
                            std::cout << "unknown xml command: " << st.toStdString() << std::endl;
                        }
                        break;

                    case 'w':
                        if(firstStage == 1 && st.contains("width"))
                        {
                            int i = st.indexOf('>');
                            i++;
                            QStringRef sub(&st, i, st.indexOf('<', i) - i);
                            width = sub.toInt();
                        }
                        else
                        {
                            std::cout << "unknown xml command: " << st.toStdString() << std::endl;
                        }
                        break;

                    default:
                        std::cout << "Unknown character while reading File" << std::endl;
                }
            }
            else
            {
                std::cout << "not <" << std::endl;
            }

            fs.getline(buf, 256);
            st = QString(buf);
        }

        fs.close();
    }
    else
    {
        std::cout << "Error opening font file" << std::endl;
    }

    #ifdef DEBUG_FONTREADER
    std::cout << currentLetter->toString().toStdString() << std::endl;
    #endif

    m_letterAmount = letterAmount;

    return 0;
}
