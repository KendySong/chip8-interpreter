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
    ImGui::SetNextWindowSizeConstraints(ImVec2(768, 314), ImVec2(768, Settings::windowHeight));
    ImGui::Begin("Console");

    if (ImGui::Button("Clear"))
    {
        _textBuffer.clear();
    }

    ImGui::Separator();
    ImGui::BeginChild("console log");
    ImGui::TextUnformatted(_textBuffer.begin());
    ImGui::EndChild();

    ImGui::End();
}

void ConsoleLog::AddLog(const char* log)
{
    _textBuffer.append(log);
}