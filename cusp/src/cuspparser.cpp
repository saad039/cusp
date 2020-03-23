#include "cusppch.h"
#include "cuspparser.h"
#include<iomanip>



cuspParser::cuspParser(Json json)
	:tree(std::move(json))
{
}

void cuspParser::generatePremakeFiles()
{
	const auto projects = this->getProjects();
	for (const auto& project : projects) {
		this->getProjectPremakeScript(project);
	}
}

const std::string cuspParser::getSolutionName(){
	return this->tree["workspace"];
}

std::string cuspParser::getArchitecture()
{
	const std::string& arch = this->tree["architecture"];
	if (arch == "32bit" || arch == "x86")
		return std::string("x86");
	return std::string("x86_64");
}

const std::string cuspParser::getToolset()
{
	return this->tree["toolset"];
}

std::vector<Project> cuspParser::getProjects()
{
	std::vector<Project> projects;
	std::for_each(std::begin(tree["projects"]), std::end(tree["projects"]),
		[&](Json& p) {
			projects.emplace_back(p["projectname"], p["cppdialect"]
									,p["kind"], p["links"]);
		}
	);
	return projects;
}


std::string cuspParser::getProjectKind(const Project& p)
{
	const auto& kind = p.Kind();
	if (kind == "consoleapp")
		return "ConsoleApp";
	else if (kind == "static")
		return "StaticLib";
	else
		return "SharedLib";
}

std::vector<std::string> cuspParser::getProjectNames()
{
	std::vector<std::string> names;
	std::for_each(std::begin(tree["projects"]), std::end(tree["projects"]),
		[&](Json& p) {
			names.emplace_back(p["projectname"]);
		});
	return names;
}

std::string cuspParser::getTargetDirectoryPath(const std::string& projectName)
{
	return std::string(projectName + "/bin/%{cfg.buildcfg}");
}

std::string cuspParser::getObjectDirectoryPath(const std::string& projectName)
{
	return std::string(projectName+"/bin-init/%{cfg.buildcfg}");
}

std::string cuspParser::getBuildDataLocation(const std::string& projectName)
{
	return std::string(projectName+"/build");
}

std::string cuspParser::getSourceFilesPath(const std::string& projectName)
{
	return std::string(projectName+"/src");
}

std::string cuspParser::getIncludeFilesPath(const std::string& projectName)
{
	return std::string(projectName+"/include");
}

std::vector<std::string> cuspParser::getProjectsToLinkTo(const Project& project)
{
	const auto names = this->getProjectNames();
	std::vector<std::string> projectsToLink;
	std::for_each(std::begin(project.Libs()), std::end(project.Libs()),
		[&](const std::string& lib) {
			if (std::find(std::begin(names), std::end(names), lib) != std::end(names))
				projectsToLink.push_back(lib);
		}
	);
	return projectsToLink;
}

std::vector<std::string> cuspParser::getIncludeDirectoriesPaths(const Project& p)
{
	const auto projectsToLink = this->getProjectsToLinkTo(p);
	std::vector<std::string> paths;
	for (const auto& p : projectsToLink) 
		paths.emplace_back(std::string(p) + "/include");
	
	paths.emplace_back(p.Name() + "/include");
	return paths;
}

//TODO: query the user about static runtime availibility
//TODO: For now two primary configurations debug and release are supported. For custom configurations, functionality will be added on later.
tsl::ordered_map<std::string, std::variant<std::string, std::vector<std::string>, std::map<std::string, std::string>>>
	cuspParser::getProjectPremakeConfiguration(const Project& project)
{
	tsl::ordered_map<std::string, 
			std::variant<std::string, std::vector<std::string>,std::map<std::string,std::string> >> cfg;

	cfg["project"]  = project.Name();
	cfg["location"] = this->getBuildDataLocation(project.Name());
	cfg["kind"] = this->getProjectKind(project);
	cfg["language"] = "C++";
	cfg["toolset"] = this->getToolset();
	cfg["cppdialect"] = project.CppDialect();
	cfg["staticruntime"] = "on";
	cfg["targetdir"] = this->getTargetDirectoryPath(project.Name());
	cfg["objdir"] = this->getObjectDirectoryPath(project.Name());

	const auto headers  = this->getIncludeFilesPath(project.Name());
	const auto srcFiles = this->getSourceFilesPath(project.Name());

	cfg["files"] = std::vector<std::string>{headers+"**.h" ,headers + "**.hpp",srcFiles + "**.cc",srcFiles + "**.cpp" };
	cfg["includedirs"] = this->getIncludeDirectoriesPaths(project);
	cfg["links"] = this->getProjectsToLinkTo(project);

	std::map<std::string, std::string> debug,release;
	debug["defines"] = "DEBUG";
	debug["runtime"] = "Debug";
	debug["symbols"] = "on";

	cfg["configurations:Debug"] = std::move(debug);

	release["defines"] = "NDEBUG";
	release["runtime"] = "Release";
	release["optimize"] = "on";

	cfg["configurations:Release"] = std::move(release);
	return cfg;

}

std::string cuspParser::getProjectPremakeScript(const Project& p){
	auto configuration = this->getProjectPremakeConfiguration(p);
	std::stringstream stream;

	for (auto& pair : configuration) {

		if(auto value = std::get_if<std::string>(&(pair.second))){
			const auto& data = *value;
			if (pair.first == "targetdir" || pair.first == "objdir") 
				stream <<'\t'<< pair.first << " (" << std::quoted(data) << ")\n";
			else 
				if(pair.first =="project")
					stream << pair.first << " " << std::quoted(data) << "\n";
				else 
					stream << '\t' << pair.first << " " << std::quoted(data) << "\n";
		}

		else if (auto value = std::get_if<std::vector<std::string>>(&(pair.second))) {
			const auto& data = *value;
			if (!data.empty()) {
				stream << '\t' << pair.first << "{\n";
				for (int i = 0, len = data.size() - 1; i < len; i++)
					stream << "\t\t" << std::quoted(data[i]) << ",\n";
				stream << "\t\t" << std::quoted(data[data.size() - 1]) << "\n\t}\n";
			}
		}

		else if (auto value = std::get_if<std::map<std::string, std::string>>(&(pair.second))) {
			const auto& data = *value;
			stream << "\t" << "filter " << std::quoted(pair.first) << "\n" ;
			for (auto& pair : data) {
				if (pair.first == "defines")
					stream << "\t\t" << pair.first << " {" << std::quoted(pair.second) << "} \n";
				else
					stream << "\t\t" << pair.first << " " << std::quoted(pair.second) << '\n';
			}
		}
	}

	std::string path;
	auto cwd = std::filesystem::current_path().string();
	auto workspace = this->tree["workspace"];
	std::cout << "Workspace: " << workspace << std::endl;
	if (cwd.find(workspace) != std::string::npos)
		path = p.Name() + "/premake5.lua";
	else{
		path = std::move(workspace);
		path += '/';
		path += p.Name();
		path += "/premake5.lua";
	}
	

	std::ofstream outFile(path);
	if (outFile.is_open()) 
		outFile << stream.str() << std::endl;
	else {
#if defined DEBUG
		throw std::runtime_error("Failed to create premake5.lua for " + p.Name());
#elif defined NDEBUG
		__SET_PATTERN_COL__;
		LOG_ERROR("Failed to create project configuration file");
		EXIT_EXECUTION;
#endif
	}
	return stream.str();
}

