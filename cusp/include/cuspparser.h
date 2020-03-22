#ifndef CUSPPARSER_H
#define CUSPPARSER_H
#include<string>
#include<string_view>
#include<vector>
#include"json.hpp"
#include"project.h"
#include<variant>
// Cusp parser's sole job is to convert cusp.json to premake5.lua
class cuspParser
{
	using Json = nlohmann::json;
private:

	Json tree;
	
	const std::string& getSolutionName();
	std::string getArchitecture();
	const std::string& getToolset();
	std::vector<Project> getProjects();
	std::string getProjectKind(const Project& p);
	std::vector<std::string> getProjectNames();

	std::string getTargetDirectoryPath(const std::string& projectName);
	std::string getObjectDirectoryPath(const std::string& projectName);
	std::string getBuildDataLocation(const std::string& projectName);

	std::string getSourceFilesPath(const std::string& projectName);   
	std::string getIncludeFilesPath(const std::string& projectName);

	std::vector<std::string> getProjectsToLinkTo(const Project& project);
	std::vector<std::string> getIncludeDirectoriesPaths(const Project& p);

	std::map<std::string, std::variant<std::string, std::vector<std::string>, std::map<std::string, std::string>>>
		getProjectPremakeConfiguration(const Project& project);

	void generateProjectPremakeConfigurationFile(const Project& p);
public:
	
	cuspParser(Json json);
	cuspParser(const cuspParser&)				 = delete;
	cuspParser& operator =(const cuspParser&)	 = delete;
	cuspParser(cuspParser&&)					 = default;
	cuspParser& operator=(cuspParser&&)			 = default;
	~cuspParser()								 = default;



};

#endif // !CUSPPARSER_H
