#include "filehandler.h"

/**
 * @brief FileHandler::FileHandler
 */
FileHandler::FileHandler()
{
    this->m_pid = 0; // zero out counter ids
    this->m_fid = 0;
    this->m_did = 0;
    this->lastError = 0;

}
/**
 * @brief FileHandler::create_project
 * creates project and associated files.
 * @param std::string name
 * @return Project* created project
 */
Project* FileHandler::create_project(std::string projName){
    Project* proj =  new Project(this->m_pid, projName);
    this->m_projects.insert(std::make_pair(proj->m_id, proj));
    save_project(proj);
    this->m_pid++;
    return proj;
}
/**
 * @brief FileHandler::create_directory
 * @param dirpath
 * @return unique directory ID
 */
ID FileHandler::create_directory(std::string dirpath){
    this->lastError = make_dir(dirpath); //varying implementation, OS dependant
    ID id = this->add_dir(dirpath);
    return id;
}

/**
 * @brief FileHandler::delete_directory
 * @param id
 * @return errorcode, if deletion was done code is 0;
 * otherwise see OS relevant directoryfile.
 */
FH_ERROR FileHandler::delete_directory(ID id){
    FH_ERROR err = remove_dir(this->get_dir(id)); //varying implementation, OS dependant
    return err;
}

/**
 * @todo unfinished, needs full project structure
 * and program to file parser to finish
 * @brief FileHandler::save_project
 * @param Project* name
 * Creates project and associated files.
 * @return void
 */
void FileHandler::save_project(Project* proj){
    std::string fileName = proj->m_name + std::string(".txt"); //filename
    ID dirID = create_directory(std::string(WORKSPACE) + "/"+ proj->m_name);//project directory

    proj->files->dir = dirID;

    proj->files->f_proj = create_file(fileName, dirID); //create project file


    fileName = proj->m_name + "_videos.txt";
    proj->files->f_videos = create_file(fileName, dirID); //create video file
    write_file(proj->files->f_proj, fileName);

    fileName = proj->m_name + "_analyses.txt";
    proj->files->f_analysis = create_file(fileName, dirID); //create analysis file
    write_file(proj->files->f_proj, fileName);

    fileName = proj->m_name + "_drawings.txt";
    proj->files->f_drawings =create_file(fileName, dirID); //create drawings file
    write_file(proj->files->f_proj, fileName);

    update_proj_files(proj);

}
/**
 * @todo unfinished, will be released with parser
 * however, is needed for creating
 * @brief FileHandler::save_project
 * @param Project* name
 * Creates project and associated files.
 * @return void
 */
void FileHandler::update_proj_files(Project* proj){
    std::string filePath = std::string(WORKSPACE) + "/" + proj->m_name + "/" + proj->m_name + std::string("_videos.txt");
    std::stringstream sstr;
    sstr << *proj;
    write_file(proj->files->f_videos, sstr.str());
}

/**
 * @todo unfinished, will be released with parser, needs full
 * project structure and file to program parser to finish.
 * @brief FileHandler::load_project
 * @param std::string, fileopath to project file
 * Load a project object from a given filepath
 */
Project* FileHandler::load_project(std::string filePath){
    Project* proj = new Project();    
    return proj;
}

/**
 * @brief FileHandler::delete_project
 * Deletes project, its associated files and contents.
 * OBS! This operation is as of now irreversible
 * @param Project*
 * @return FH_ERROR errorcode
 */
FH_ERROR FileHandler::delete_project(Project* proj){
    ProjFiles* pf = proj->files;
    delete_file(pf->f_proj);
    delete_file(pf->f_videos);
    delete_file(pf->f_analysis);
    delete_file(pf->f_drawings);
    return delete_directory(proj->files->dir);

}
/**
 * @todo make threadsafe
 * @brief FileHandler::add_video
 * @param Project*, std::string
 * Add a video filepath to a given project.
 * Creates Video object which is accessed further by returned id.
 */
void FileHandler::add_video(Project* proj, std::string filePath){
    Video* v = new Video(this->m_fid, filePath);
    proj->add_video(v);
    this->add_file(filePath);
}

 /**
  * @brief FileHandler::create_file
  * create a file by given name in already excisting
  * application tracked directory
  * @param std::string file name, ID directory id
  */

ID FileHandler::create_file(std::string filename, ID dirID){
    std::ofstream f;
    std::string filePath = this->get_dir(dirID)+"/"+filename;
    f.open(filePath.c_str());

    return this->add_file(filePath);
  }
/**
 * @todo make threadsafe
 * @brief FileHandler::delete_file
 * delete application tracked file
 * @param ID file id
 */
 FH_ERROR FileHandler::delete_file(ID id){
    std::string file = this->get_file(id);
    return std::remove(file.c_str());
 }
 /**
  * @todo make threadsafe
  * @brief FileHandler::write_file
  *  Write given text to an application tracked file
  * @param ID file id, std::string text
  * @return void
  */
 void FileHandler::write_file(ID id, std::string text){
    std::string fileName = this->get_file(id);
    std::ofstream f (fileName.c_str(), std::ios::in | std::ios::out | std::ios::ate);
    f << text.c_str() << std::endl;
 }

 /**
  * @brief FileHandler::read_file
  *  Read given lenght of lines to buffer from application
  *  tracked file. OBS! If number of lines exceeds =>
  *  reads to end of file (EOF)
  *  @param ID file id, std::string text
  *  @return voi
  */
 void FileHandler::read_file(ID id, size_t linesToRead, std::string& buf){
     std::ifstream f(this->get_file(id));
     while(linesToRead-- && std::getline(f,buf));
 }
 /**
  * @brief FileHandler::get_project
  * Getter
  * @param ID project id
  * @return Project*
  */
 Project* FileHandler::get_project(ID pid){
    this->projMapLock.lock();
    Project* p = this->m_projects.at(pid);
    this->projMapLock.unlock();
    return p;
 }
 /**
  * @brief FileHandler::get_file
  * Getter
  * @param ID project file id
  * @return std::string filepath
  */
 std::string FileHandler::get_file(ID id){
    this->fileMapLock.lock();
    std::string file = this->m_fileMap.at(id);
    this->fileMapLock.unlock();
    return file;
 }
 /**
  * @brief FileHandler::get_dir
  * @param ID directory id
  * @return directory path
  */
 std::string FileHandler::get_dir(ID id){
    this->dirMapLock.lock();
    std::string dir = this->m_dirMap.at(id);
    this->dirMapLock.unlock();
    return dir;
 }

 /**
  * @brief FileHandler::add_projectr
  * @param std::pari<<ID, Project*> pair
  * @return void
  */
 void FileHandler::add_project(std::pair<ID,Project*> pair){
    this->projMapLock.lock();
    this->m_projects.insert(pair);
    this->projMapLock.unlock();

 }
 /**
  * @brief FileHandler::add_file
  * @param std::string filepath
  * @return unique file identifier
  */
ID FileHandler::add_file(std::string filepath){
    std::pair<ID,std::string> pair = std::make_pair(this->m_fid, filepath);
    this->fileMapLock.lock();
    this->m_fileMap.insert(pair);
    this->fileMapLock.unlock();
    return this->m_fid++;
 }
 /**
  * @brief FileHandler::add_dir
  * @param std::string dirpath
  * @return unique directory identifier
  */
ID FileHandler::add_dir(std::string dirpath){
    std::pair<ID,std::string> pair = std::make_pair(this->m_did, dirpath);
    this->dirMapLock.lock();
    this->m_dirMap.insert(pair);
    this->dirMapLock.unlock();
    return this->m_did++;
 }
