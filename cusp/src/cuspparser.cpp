#include "cusppch.h"
#include "cuspparser.h"

cuspParser::cuspParser(Json json)
	:tree(std::move(json))
{
}

const std::string& cuspParser::getSolutionName()
{
	return this->tree["workspace"];
}

std::string cuspParser::getArchitecture()
{
	const std::string& arch = this->tree["architecture"];
	if (arch == "32bit" || arch == "x86")
		return std::string("x86");
	return std::string("x86_64");
}

const std::string& cuspParser::getToolset()
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
	return std::string(projectName + "/bin/");
}

std::string cuspParser::getObjectDirectoryPath(const std::string& projectName)
{
	return std::string(projectName+"/bin-init/");
}

std::string cuspParser::getBuildDataLocation(const std::string& projectName)
{
	return std::string(projectName+"/build/");
}

std::string cuspParser::getSourceFilesPath(const std::string& projectName)
{
	return std::string(projectName+"/src/");
}

std::string cuspParser::getIncludeFilesPath(const std::string& projectName)
{
	return std::string(projectName+"/include/");
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
		paths.emplace_back(std::string(p) + "/include/");
	
	paths.emplace_back(p.Name() + "/include/");
	return paths;
}

//TODO: query the user about static runtime availibility
//TODO: For now two primary configurations debug and release are supported. For custom configurations, functionality will be added on later.
std::map<std::string, std::variant<std::string, std::vector<std::string>, std::map<std::string, std::string> >>
	cuspParser::getProjectPremakeConfiguration(const Project& project)
{
	std::map<std::string, 
			std::variant<std::string, std::vector<std::string>,std::map<std::string,std::string> >> script;

	script["project"]  = project.Name();
	script["location"] = this->getBuildDataLocation(project.Name());
	script["kind"] = this->getProjectKind(project);
	script["language"] = "C++";
	script["toolset"] = this->getToolset();
	script["cppdialect"] = project.CppDialect();
	script["staticruntime"] = "on";
	script["targetdir"] = this->getTargetDirectoryPath(project.Name());
	script["objdir"] = this->getObjectDirectoryPath(project.Name());
	script["files"] = std::vector<std::string>{ this->getIncludeFilesPath(project.Name()), this->getSourceFilesPath(project.Name()) };
	script["includedirs"] = this->getIncludeDirectoriesPaths(project);
	script["links"] = this->getProjectsToLinkTo(project);

	std::map<std::string, std::string> debug,release;
	debug["defines"] = "DEBUG";
	debug["runtime"] = "Debug";
	debug["symbols"] = "on";

	script["configurations:Debug"] = std::move(debug);

	release["defines"] = "NDEBUG";
	release["runtime"] = "Release";
	release["optimize"] = "on";

	script["configurations:Release"] = std::move(release);
	return script;

}

void cuspParser::generateProjectPremakeConfigurationFile(const Project& p)
{
	auto configuration = this->getProjectPremakeConfiguration(p);
	std::stringstream stream;

	for (auto& pair : configuration) {
		if(auto value = std::get_if<std::string>(&(pair.second))){

		}
		else if (auto value = std::get_if<std::vector<std::string>>(&(pair.second))) {

		}
		else if (auto value = std::get_if<std::map<std::string, std::string>>(&(pair.second))) {

		}
	}

}


