#ifndef PROJECT_H
#define PROJECT_H
#include <map>
#include <string>
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include "filehandler.h"
#include "videoproject.h"
#include "video.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
typedef int ID;

/**
 * @brief The Project struct
 * incomplete struct, will be added on
 * along with parser functionality
 */

struct Project{
public:
    Project();
    Project(ID id, std::string name);
    Project(std::string dir_path);
    ~Project();
    ID add_video(Video *vid);
    void remove_video_project(ID id);
    // read and write operator for Projects
    void read(const QJsonObject& json);
    void write(QJsonObject& json);

// TODO
//    void add_analysis();
//    void add_drawing();      
public:
    ID id;
    ID v_id;
    std::string name;
    std::map<ID,VideoProject*> videos;
    ID dir;
    ID dir_videos;
    bool saved;
};


#endif // PROJECT_H
