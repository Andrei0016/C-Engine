#pragma once

#include <vector>
#include <functional>
#include <SDL_render.h>

class CommandBuffer {
public:
    CommandBuffer();
    ~CommandBuffer();

    void beginRecording();
    void endRecording();
    void submit();

    // Example of a command
    void recordCall(const std::function<void()>& callable);

private:
    std::vector<std::function<void()>> commands;
    bool recording;
};
