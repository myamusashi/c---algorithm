#pragma once
#include <string>
#include <vector>

class SourceData {
public:
    SourceData(std::vector<std::string>* data, std::vector<std::string>* dataFinish);
    void AddData(std::vector<std::string>* mainData);
    void CompletedData(std::vector<std::string>* taskSucced);
    void DisplayData(std::vector<std::string>* mainData);
    void DisplayFinishData(std::vector<std::string>* taskSucced);
    void RemoveData(std::vector<std::string>* mainData, std::vector<std::string>* taskSucced);
    void EditData(std::vector<std::string>* mainData, std::vector<std::string>* taskSucced);
private:
    std::vector<std::string>* mainData; // Variabel anggota untuk menyimpan mainData
    std::vector<std::string>* taskSucced;

};