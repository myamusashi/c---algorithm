#pragma once

#include <string>
#include <vector>
// SourceData menyimpan dan mengelola tugas
class SourceData {
public:
    SourceData(std::vector<std::string>* data, std::vector<std::string>* doWork, std::vector<std::string>* dataFinish); // Constructor kelas untuk menerima tiga parameter pointer vector string
    void AddTask(std::vector<std::string>* mainData);
    void TasktoDo(std::vector<std::string>* toDo);
    void CompletedTask(std::vector<std::string>* taskSucced);
    void DisplayTask(std::vector<std::string>* mainData);
    void DisplayTaskToDo(std::vector<std::string>* toDo);
    void DisplayCompletedTask(std::vector<std::string>* taskSucced);
    void RemoveTask(std::vector<std::string>* mainData);
    void RemoveTaskToDo(std::vector<std::string>* toDo);
    void RemoveFinishTask(std::vector<std::string>* taskSucced);
    void EditTask(std::vector<std::string>* mainData);
    void EditTaskTodo(std::vector<std::string>* toDo);
    void EditFinishTask(std::vector<std::string>* taskSucced);
private:
    std::vector<std::string>* mainData; // Variabel anggota untuk menyimpan mainData
    std::vector<std::string>* toDo;
    std::vector<std::string>* taskSucced;
};