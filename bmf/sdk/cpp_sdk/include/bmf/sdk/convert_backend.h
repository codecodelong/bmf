#pragma once

#include <bmf/sdk/common.h>
#include <bmf/sdk/video_frame.h>

namespace bmf_sdk {

class Convertor
{
    Convertor(MediaDesc dp);
    virtual int media_cvt(MediaDesc &dp);
    virtual int format_cvt(MediaDesc &dp);
    virtual int device_cvt(MediaDesc &dp);
};

BMF_API void set_convertor(std::string &media_type, Convertor convertor);
BMF_API Convertor *get_convertor(std::string &media_type);

BMF_API VideoFrame *bmf_convert(VideoFrame vf, MediaDesc &dp);

template<typename ...Args>
struct Register {
    using RegisterFunc = void(*)(Args ...args);
    explicit Register(RegisterFunc func, Args...args){
        func(args...);
    }
};

#define BMF_REGISTER_CONVERTOR(media_type, convertor) \
        static Register<std::string, Convertor> \
            __i##media##convertor(set_convertor, media_type, convertor);

} //namespace bmf_sdk