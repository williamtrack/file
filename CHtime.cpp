#include "CHtime.h"

#include <iostream>

void CHtime::pt()
{
    gettm(getTimeStamp());
}

void CHtime::pt(const char* tag)
{
    std::cout << tag << ": ";
    gettm(getTimeStamp());
}

std::string CHtime::gt()
{
    time_t milli = getTimeStamp() + (std::time_t)8 * 60 * 60 * 1000;
    auto mTime = std::chrono::milliseconds(milli);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);

    struct tm now;
    gmtime_s(&now, &tt);
    std::string result
        = std::to_string(now.tm_min) + ":"
        + std::to_string(now.tm_sec) + ":"
        + std::to_string(milli % 1000);
    return result;
}

std::time_t CHtime::getTimeStamp()
{
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count();
    //std::time_t timestamp = std::chrono::system_clock::to_time_t(tp);
    return timestamp;
}

std::tm* CHtime::gettm(std::time_t timestamp)
{
    std::time_t milli = timestamp + (std::time_t)8*60*60*1000;//此处转化为东八区北京时间，如果是其它时区需要按需求修改
    auto mTime = std::chrono::milliseconds(milli);
    auto tp = std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>(mTime);
    auto tt = std::chrono::system_clock::to_time_t(tp);

    struct tm now;
    gmtime_s(&now, &tt);
    printf("%02d:%02d:%02d.%03d\n", now.tm_hour, now.tm_min, now.tm_sec, (int)(milli % 1000));
    //printf("%03lld\n", milli);
    
    //std::tm* now = std::gmtime(&tt);
    //printf("%4d年%02d月%02d日 %02d:%02d:%02d.%d\n", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, milli % 1000);
    return &now;
}
