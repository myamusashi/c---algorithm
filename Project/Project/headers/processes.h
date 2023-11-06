#pragma once
#include <mongocxx/client.hpp>
#include <string>

class SourceData {
public:
    SourceData(const std::string& conn, const std::string& dbs, const std::string& taskqueue, const std::string& taskstodo, const std::string& finishedtasks);     
    void AddTask();
    void TasktoDo();
    void CompletedTask();
    void DisplayTask();
    void DisplayTaskToDo();
    void DisplayCompletedTask();
    void RemoveTask();
    void RemoveTaskToDo();
    void RemoveFinishTask();
    void EditTask();
    void EditTaskTodo();
    void EditFinishTask();

private:
    mongocxx::client connection_;
    mongocxx::database database_;
    mongocxx::collection newTasks_;
    mongocxx::collection inProgress_;
    mongocxx::collection completedTask_;
};
