#include "CommandBuffer.h"

CommandBuffer::CommandBuffer() : recording(false) {}

CommandBuffer::~CommandBuffer() {}

void CommandBuffer::beginRecording() {
    commands.clear();
    recording = true;
}

void CommandBuffer::endRecording() {
    recording = false;
}

void CommandBuffer::recordCall(const std::function<void()>& callable) {
    if (recording) {
        commands.push_back(callable);
    }
}

void CommandBuffer::submit() {
    for (const auto& command : commands) {
        command();
    }
}
