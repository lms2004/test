#include "ProjectScore.h"
#include<iostream>
#include <algorithm>
#include <QDebug>
#include <sstream>
#include <functional>
#include <algorithm>

using namespace std;
////根据权重进行成绩修改;
//void ProjectSorting::adjustGradesByTypeWeight(std::vector<Project>& projects, std::unordered_map<std::string, float> typeWeights) {
//	vector <Project>::iterator project = projects.begin();
//	while (project != projects.end()) {
//		auto it = typeWeights.find(project->type);
//		if (it != typeWeights.end())//查到相应类型;
//		{
//			project->grade *= it->second;//修改该值;
//			++project;
//		}
//
//		else {//未找到相应类型;
//			auto it = NoFindTypeWeight(project, typeWeights);
//			project = it;
//		}
//	}
//	cout << "已成功修改所有成绩!" << endl;
//}
//
////用于未找到权重的错误处理;
//vector <Project>::iterator ProjectSorting::NoFindTypeWeight(vector <Project>::iterator& project, unordered_map<std::string, float>& typeWeights) {
//	cerr << "未找到type为" << project->type << "的权重" << endl;
//	cout << "请确保该项目的类型" << project->type << "正确" << endl;
//	cout << "按0使用默认权重1.0;" << endl << "按1添加该类型权重;" << endl << "按2修改项目的类型;" << endl;
//	cout << "请输入你的选择: ";
//
//	int a = Select1or2or0();//定义用户选择;
//
//	if (a == 1) {
//		SelectNoFindTyWe1(project, typeWeights);
//		return ++project;
//	}//若输入为1,则增添该类型的权重;
//
//	else if (a == 0) {
//		SelectNoFindTyWe0(project, typeWeights);
//		return ++project;
//	}//若输入为0,则权重为1.0,成绩不变;
//
//	else {
//		SelectNoFindTyWe2(project);//若输入为2,则重新对该项目进行修改;
//		return project;
//	}
//
//}
//
////用于得到用户对于未发现typeweight问题相关处理的选择;
//int ProjectSorting::Select1or2or0() {
//	int a;//定义用户选择;
//	cin >> a;
//	int s = cin.rdstate();//判断用户输入的是否为数字且为0或1或2;
//	while (s || (a != 0 && a != 1 && a != 2)) {
//		cin.clear();
//		cerr << "输入非法!请重新输入: ";
//		while (cin.get() != '\n');
//		cin >> a;
//		s = cin.rdstate();//输入错误处理;
//	}
//	return a;
//}
//
////用于用户选择0处理问题(使用默认权重1.0)
//void ProjectSorting::SelectNoFindTyWe0(vector <Project>::iterator& project, unordered_map<std::string, float>& typeWeights) {
//	cout << "是否保存该权重,(若保存则以后都使用该权重1.0)" << endl;
//	cout << "输入1表示是,输入2表示否,输入0表示退出:";
//	int a;//定义用户选择;
//	a = Select1or2or0();//用户选者1or2or0;
//	if (a == 1) {//用户输入1,保存该类型的权重;
//		pair<string, float> NewtypeWeight;
//		NewtypeWeight.first = project->type;
//		NewtypeWeight.second = 1.0;
//		typeWeights.insert(NewtypeWeight);
//		cout << "添加成功!" << endl;
//		cout << "已成功修改该类型的成绩!" << endl;
//		return;
//	}
//	return;//用户输入2,0,不做处理;
//}
//
////用于用户选择1处理问题(添加该类型的权重)
//void ProjectSorting::SelectNoFindTyWe1(vector <Project>::iterator& project,
//	unordered_map<std::string, float>& typeWeights) {
//	pair<string, float> NewtypeWeight;
//	NewtypeWeight.first = project->type;
//	cout << "请输入权重: ";
//	cin >> NewtypeWeight.second;
//	typeWeights.insert(NewtypeWeight);
//	cout << "添加成功!" << endl;
//	project->grade *= NewtypeWeight.second;
//	cout << "已成功修改该类型的成绩!" << endl;
//	return;
//}
//
////用于用户选择2处理问题(修改项目的类型)
//void ProjectSorting::SelectNoFindTyWe2(vector <Project>::iterator& project) {
//	cout << "请输入修改后的该项目类型: ";
//	cin >> project->type;
//	cout << endl << "修改成功" << endl;
//	return;
//}
//
////自动排序;
//void  ProjectSorting::sortAndPickTopByType(vector<Project>& projects) {
//	sort(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
//		return a > b;
//		});//lambda函数和sort函数选择;
//}
//
//
////去重项目;保留每个类型的最高成绩;
//void ProjectSorting::deduplicateByTypeAndGrade(std::vector<Project>& projects) {
//	sortAndPickTopByType(projects);//去重前先排序;
//	projects.erase(unique(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
//		return a == b;
//		}), projects.end());//lambda函数和erase函数去重;
//}
//
//
////修改项目成绩;
//void ProjectSorting::updateProjectGrade(Project& project, float newGrade, float min, float max) {
//	if (newGrade >= min && newGrade <= max) {
//		cout << "输入成绩合法!" << endl;
//		project.grade = newGrade;
//		cout << "已成功修改成绩!" << endl;
//		return;
//	}//输入成绩在该范围内;
//	else {//输入成绩不在范围内;
//		cerr << "输入成绩非法!";
//		while (newGrade<min || newGrade>max) {
//			cout << "请重新输入成绩或则按-1退出: ";
//			newGrade = RegetupdateProjectGrade();//重新获取newGrade;
//			if (newGrade == -1) {
//				cout << "已成功退出!" << endl;//退出程序;
//				return;
//			}
//			else {
//				updateProjectGrade(project, newGrade);
//				return;
//			}//若不退出,则重新修改成绩;
//		}
//	}
//}
//
////修改项目错误处理
//int ProjectSorting::RegetupdateProjectGrade() {
//	int newGrade;
//	cin >> newGrade;
//	int s = cin.rdstate();
//	while (s) {//判断输入的是否为数字;
//		cin.clear();
//		cerr << "输入的不是数字!" << endl;
//		cout << "请重新输入或按-1退出: ";
//		while (cin.get() != '\n');
//		cin >> newGrade;
//		s = cin.rdstate();//判断输入的是否为数字;
//	}
//	return newGrade;
//}
//
////添加项目;
//void  ProjectSorting::AddProjects(std::vector<Project>& projects, Project& project) {
//	auto it = find_if(projects.begin(), projects.end(), [&project](Project& a)->bool {
//		return (a.name == project.name) && (a.type == project.type);
//		});
//	if (it != projects.end()) {
//		cout << "已存在该项目!" << endl;
//		if (it->grade != project.grade) {
//			cout << "但该项目的成绩与已存在的项目成绩不同,是否修改(输入1表示是,输入2表示否,输入0表示退出程序;)";
//			int a = Select1or2or0();
//			if (a == 1)
//				it->grade = project.grade;
//			else
//				return;
//		}
//	}
//}
//
////删除项目;
//void ProjectSorting::DeleteProjects(std::vector<Project>& projects, Project& project) {
//	auto it = find(projects.begin(), projects.end(), project);
//	if (it != projects.end()) {
//		projects.erase(it);//删除该项目;
//	}
//	else {//未找到删除项目;
//		cerr << "未找到该项目!" << endl;
//		cout << "删除的项目确定是:" << endl
//			<< "name: " << project.name << endl
//			<< "type: " << project.type << endl
//			<< "grade: " << project.grade << endl;
//		cout << "请选择:" << endl;
//		cout << "1:执行查找操作,查看已知项目是否有名字为" << project.name << "的项目" << endl
//			<< "2:执行修改操作,修改所需删除的项目" << endl
//			<< "0:退出操作";
//		int a = Select1or2or0();//用户选择;
//		if (a == 1) {
//
//		}
//
//
//	}
//
//}
//
//
//
ProjectMysql::ProjectMysql() {
	//初始化数据库
	mysql_init(&mysql);
	//设置字符编码
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//连接数据库
	//这里需要输入自己的本机名和密码，若全为默认，只需更改*处为自己的密码以及”xsgl“处改成自己创建的数据库即可
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "test", 3306, NULL, 0) == NULL) {
		printf("错误原因: %s\n", mysql_error(&mysql));
		printf("连接失败！\n");
		exit(-1);
	}
	string sql = "CREATE TABLE IF NOT EXISTS users(\
		username VARCHAR(20) NOT NULL,\
		hashed_password VARCHAR(128) NOT NULL,\
		salt VARCHAR(100) NOT NULL,\
		PRIMARY KEY(username)\
	)";

	int re = mysql_query(&mysql, sql.c_str());
	//创建projects和backup_projects的表;
	sql = "CREATE TABLE IF NOT EXISTS projects( \
         name varchar(100),\
		 type varchar(100),\
		 grade varchar(10),\
         path  varchar(100),\
		 user_name varchar(20),\
		 FOREIGN KEY(user_name) REFERENCES users(username)\
		 ) ";
	re = mysql_query(&mysql, sql.c_str());//从字符串换成const char*
	if (re != 0)
	{
		//std::cout << "初始化失败" << mysql_error(&mysql) << end
		return;
	}

	//创建backup_projects;用于备份数据;
	sql = "CREATE TABLE IF NOT EXISTS backup_projects ( \
           name varchar(100),\
		   type varchar(100),\
		   grade varchar(10),\
           path  varchar(100),\
		   user_name varchar(20)\
		   )  ";
	re = mysql_query(&mysql, sql.c_str());//从字符串换成const char*
	if (re != 0)
	{
		//std::cout << "初始化失败!" << mysql_error(&mysql) << endl;
		return;
	}
}

//将mysql的数据写入到Projects中;
void ProjectMysql::OutputProject(vector<Project>& projects) {
	string sql = "select * from projects where user_name=123;";
	int ret = mysql_query(&mysql, sql.c_str());
	// 获取结果集
	MYSQL_RES* res = mysql_store_result(&mysql);
	// 如果结果集为空，则直接返回
	if (res == NULL) {
		return;
	}
	while (MYSQL_ROW row = mysql_fetch_row(res)) {
		string s1 = row[0]; // 直接使用字符串
		string s2 = row[1]; // 直接使用字符串
		string s3 = row[2]; // 直接使用字符串
		string s4 = row[3]; // 直接使用字符串
		Project project(s1, s2, s3, s4);
		projects.push_back(project);
	}
	mysql_free_result(res); // 释放结果集内存

	//将剩余数据拷贝到backup_projects;
	mysql_query(&mysql, "truncate table bacup_projects ");
	//将projects中的数据按name_user名字升序排序;
	sql = "insert into backup_projects select * from projects where user_name!=123 oder by name_user;";
	mysql_query(&mysql, sql.c_str());

}

void  ProjectMysql::InputProject(vector<Project>& projects) {
	//写入数据;
	string sql;
	mysql_query(&mysql, "truncate table projects ");
	vector <Project>::iterator project = projects.begin();
	while (project != projects.end()) {
		string str = "insert  into  projects  values('" + project->name + "' ,'" + project->type + "', '" + project->grade + "','" + project->path + "',123);";
		mysql_query(&mysql, str.c_str());
		//qDebug() << project->name;
		project++;
	}

	//将备份中的数据写入到projects中;
	sql = "INSERT INTO projects\
	SELECT* FROM backup_projects\
		WHERE NOT EXISTS(\
			SELECT 1 FROM projects\
			WHERE projects.user_name = backup_projects.user_name\
		); ";
	mysql_query(&mysql, sql.c_str());
	mysql_query(&mysql, "truncate table backup_projects ");
}

//去重项目;保留每个类型的最高成绩;
void ProjectSorting::deduplicateByTypeAndGrade(std::vector<Project>& projects) {
	sort(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
		return a > b;
		});//lambda函数和sort函数选择;
	projects.erase(unique(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
		return a == b;
		}), projects.end());//lambda函数和erase函数去重;
}