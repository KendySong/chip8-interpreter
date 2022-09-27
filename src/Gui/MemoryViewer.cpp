#include "MemoryViewer.hpp"

MemoryViewer* MemoryViewer::_memoryViewer = nullptr;

void MemoryViewer::HandleInterface()
{
    ImGui::Begin("Memory Viewer");
    
    ImGui::End();
}

MemoryViewer* MemoryViewer::GetInstance()
{
    if (_memoryViewer == nullptr)
    {
        _memoryViewer = new MemoryViewer();
    }
    
    return _memoryViewer;
}

std::vector<std::uint8_t>& MemoryViewer::GetMemoryRom() noexcept
{
    return _memoryRom;
}