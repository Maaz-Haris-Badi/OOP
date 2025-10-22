#include <iostream>

void convert24(int seconds)
{

    if (seconds < 60)
    {
        std::cout << "00:00:" << seconds << std::endl;
    }
    else if (seconds >= 60 && seconds < 3600)
    {
        int minutes = seconds / 60;
        int sec = seconds % 60;
        if (seconds < 10)
        {
            if (minutes > 10)
            {
                std::cout << "00:" << minutes << ":0" << sec << std::endl;
            }
            else
            {
                std::cout << "00:0" << minutes << ":0" << sec << std::endl;
            }
        }
        else
        {
            if (minutes > 10)
            {
                std::cout << "00:" << minutes << ":" << sec << std::endl;
            }
            else
            {
                std::cout << "00:0" << minutes << ":" << sec << std::endl;
            }
        }
    }

    else if (seconds >= 3600 && seconds < 86400)
    {
        int hours = seconds / 3600;
        int minutes = (seconds % 3600) / 60;
        int sec = seconds % 60;

        if (seconds < 10)
        {
            if (minutes > 10)
            {
                if (hours > 10)
                {
                    std::cout << hours << ":" << minutes << ":0" << sec << std::endl;
                }
                else
                {
                    std::cout << "0" << hours << ":" << minutes << ":0" << sec << std::endl;
                }
            }
            else
            {
                if (hours > 10)
                {
                    std::cout << hours << ":0" << minutes << ":0" << sec << std::endl;
                }
                else
                {
                    std::cout << "0" << hours << ":0" << minutes << ":0" << sec << std::endl;
                }
            }
        }
        else
        {
            if (minutes > 10)
            {
                if (hours > 10)
                {
                    std::cout << hours << ":" << minutes << ":" << sec << std::endl;
                }
                else
                {
                    std::cout << "0" << hours << ":" << minutes << ":" << sec << std::endl;
                }
            }
            else
            {
                if (hours > 10)
                {
                    std::cout << hours << ":0" << minutes << ":" << sec << std::endl;
                }
                else
                {
                    std::cout << "0" << hours << ":0" << minutes << ":" << sec << std::endl;
                }
            }
        }
    }
    else if (seconds >= 86400)
    {
        int days = seconds / 86400;
        int hours = (seconds % 86400) / 3600;
        int minutes = (seconds % 3600) / 60;
        int sec = seconds % 60;

        if (seconds > 10)
        {
            if (minutes > 10)
            {
                if (hours > 10)
                {
                    std::cout << days << " days " << hours << ":" << minutes << ":" << sec << std::endl;
                }
                else
                {
                    std::cout << days << " days " << "0" << hours << ":" << minutes << ":" << sec << std::endl;
                }
            }
            else
            {
                if (hours > 10)
                {
                    std::cout << days << " days " << hours << ":0" << minutes << ":" << sec << std::endl;
                }
                else
                {
                    std::cout << days << " days " << "0" << hours << ":0" << minutes << ":" << sec << std::endl;
                }
            }
        }
    }
}

void convert24(int seconds, int minutes)
{
    convert24(seconds + (minutes * 60));
}

void convert24(int seconds, int minutes, int hours)
{
    convert24(seconds + ((minutes * 60) + (hours * 3600)));
}

int main()
{
    int seconds, minutes, hours;

    std::cout << "Welcome to time conversion system" << std::endl;
    std::cout << "Enter hours: ";
    std::cin >> hours;
    std::cout << "Enter minutes:";
    std::cin >> minutes;
    std::cout << "Enter seconds:";
    std::cin >> seconds;

    if (seconds < 0 || minutes < 0 || hours < 0)
    {
        std::cout << "Error: Negative values are not allowed." << std::endl;
        return 1;
    }

    if (seconds >= 0 && (minutes == 0 && hours == 0))
    {
        convert24(seconds);
    }

    if ((seconds >= 0 && minutes >= 0) && hours == 0)
    {
        convert24(seconds, minutes);
    }

    if (seconds >= 0 && minutes >= 0 && hours >= 0)
    {
        convert24(seconds, minutes, hours);
    }

    return 0;
}