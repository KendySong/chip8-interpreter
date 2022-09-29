#include "ConsoleLog.hpp"

ConsoleLog* ConsoleLog::_consoleLog = nullptr;
ConsoleLog* ConsoleLog::GetInstance()
{
    if (_consoleLog == nullptr)
    {
        _consoleLog = new ConsoleLog();
    }
    return _consoleLog;
}

void ConsoleLog::HandleInterface()
{
    if (ImGui::Begin("Console"))
    {
        if (ImGui::Button("Clear"))
        {
            _addressBuffer.clear();
        }

        ImGui::SameLine();
        if (ImGui::Button("Save to file"))
        {
            SaveToFile();
        }
        
        ImGui::Separator();
        ImGui::BeginChild("console log");   
        ImGui::TextUnformatted(_addressBuffer.begin());    
        ImGui::EndChild();
    }
  
    ImGui::End();
}

void ConsoleLog::AddLog(const char* log)
{
    _addressBuffer.append(log);
}

void ConsoleLog::SaveToFile()
{
    std::ofstream writer("log.txt", std::ios::app);
    writer << _addressBuffer.begin();
    writer.close();
}