#include "ProjectScore.h"
#include<iostream>
#include <algorithm>
#include <QDebug>
#include <sstream>
#include <functional>
#include <algorithm>

using namespace std;
////����Ȩ�ؽ��гɼ��޸�;
//void ProjectSorting::adjustGradesByTypeWeight(std::vector<Project>& projects, std::unordered_map<std::string, float> typeWeights) {
//	vector <Project>::iterator project = projects.begin();
//	while (project != projects.end()) {
//		auto it = typeWeights.find(project->type);
//		if (it != typeWeights.end())//�鵽��Ӧ����;
//		{
//			project->grade *= it->second;//�޸ĸ�ֵ;
//			++project;
//		}
//
//		else {//δ�ҵ���Ӧ����;
//			auto it = NoFindTypeWeight(project, typeWeights);
//			project = it;
//		}
//	}
//	cout << "�ѳɹ��޸����гɼ�!" << endl;
//}
//
////����δ�ҵ�Ȩ�صĴ�����;
//vector <Project>::iterator ProjectSorting::NoFindTypeWeight(vector <Project>::iterator& project, unordered_map<std::string, float>& typeWeights) {
//	cerr << "δ�ҵ�typeΪ" << project->type << "��Ȩ��" << endl;
//	cout << "��ȷ������Ŀ������" << project->type << "��ȷ" << endl;
//	cout << "��0ʹ��Ĭ��Ȩ��1.0;" << endl << "��1��Ӹ�����Ȩ��;" << endl << "��2�޸���Ŀ������;" << endl;
//	cout << "���������ѡ��: ";
//
//	int a = Select1or2or0();//�����û�ѡ��;
//
//	if (a == 1) {
//		SelectNoFindTyWe1(project, typeWeights);
//		return ++project;
//	}//������Ϊ1,����������͵�Ȩ��;
//
//	else if (a == 0) {
//		SelectNoFindTyWe0(project, typeWeights);
//		return ++project;
//	}//������Ϊ0,��Ȩ��Ϊ1.0,�ɼ�����;
//
//	else {
//		SelectNoFindTyWe2(project);//������Ϊ2,�����¶Ը���Ŀ�����޸�;
//		return project;
//	}
//
//}
//
////���ڵõ��û�����δ����typeweight������ش����ѡ��;
//int ProjectSorting::Select1or2or0() {
//	int a;//�����û�ѡ��;
//	cin >> a;
//	int s = cin.rdstate();//�ж��û�������Ƿ�Ϊ������Ϊ0��1��2;
//	while (s || (a != 0 && a != 1 && a != 2)) {
//		cin.clear();
//		cerr << "����Ƿ�!����������: ";
//		while (cin.get() != '\n');
//		cin >> a;
//		s = cin.rdstate();//���������;
//	}
//	return a;
//}
//
////�����û�ѡ��0��������(ʹ��Ĭ��Ȩ��1.0)
//void ProjectSorting::SelectNoFindTyWe0(vector <Project>::iterator& project, unordered_map<std::string, float>& typeWeights) {
//	cout << "�Ƿ񱣴��Ȩ��,(���������Ժ�ʹ�ø�Ȩ��1.0)" << endl;
//	cout << "����1��ʾ��,����2��ʾ��,����0��ʾ�˳�:";
//	int a;//�����û�ѡ��;
//	a = Select1or2or0();//�û�ѡ��1or2or0;
//	if (a == 1) {//�û�����1,��������͵�Ȩ��;
//		pair<string, float> NewtypeWeight;
//		NewtypeWeight.first = project->type;
//		NewtypeWeight.second = 1.0;
//		typeWeights.insert(NewtypeWeight);
//		cout << "��ӳɹ�!" << endl;
//		cout << "�ѳɹ��޸ĸ����͵ĳɼ�!" << endl;
//		return;
//	}
//	return;//�û�����2,0,��������;
//}
//
////�����û�ѡ��1��������(��Ӹ����͵�Ȩ��)
//void ProjectSorting::SelectNoFindTyWe1(vector <Project>::iterator& project,
//	unordered_map<std::string, float>& typeWeights) {
//	pair<string, float> NewtypeWeight;
//	NewtypeWeight.first = project->type;
//	cout << "������Ȩ��: ";
//	cin >> NewtypeWeight.second;
//	typeWeights.insert(NewtypeWeight);
//	cout << "��ӳɹ�!" << endl;
//	project->grade *= NewtypeWeight.second;
//	cout << "�ѳɹ��޸ĸ����͵ĳɼ�!" << endl;
//	return;
//}
//
////�����û�ѡ��2��������(�޸���Ŀ������)
//void ProjectSorting::SelectNoFindTyWe2(vector <Project>::iterator& project) {
//	cout << "�������޸ĺ�ĸ���Ŀ����: ";
//	cin >> project->type;
//	cout << endl << "�޸ĳɹ�" << endl;
//	return;
//}
//
////�Զ�����;
//void  ProjectSorting::sortAndPickTopByType(vector<Project>& projects) {
//	sort(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
//		return a > b;
//		});//lambda������sort����ѡ��;
//}
//
//
////ȥ����Ŀ;����ÿ�����͵���߳ɼ�;
//void ProjectSorting::deduplicateByTypeAndGrade(std::vector<Project>& projects) {
//	sortAndPickTopByType(projects);//ȥ��ǰ������;
//	projects.erase(unique(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
//		return a == b;
//		}), projects.end());//lambda������erase����ȥ��;
//}
//
//
////�޸���Ŀ�ɼ�;
//void ProjectSorting::updateProjectGrade(Project& project, float newGrade, float min, float max) {
//	if (newGrade >= min && newGrade <= max) {
//		cout << "����ɼ��Ϸ�!" << endl;
//		project.grade = newGrade;
//		cout << "�ѳɹ��޸ĳɼ�!" << endl;
//		return;
//	}//����ɼ��ڸ÷�Χ��;
//	else {//����ɼ����ڷ�Χ��;
//		cerr << "����ɼ��Ƿ�!";
//		while (newGrade<min || newGrade>max) {
//			cout << "����������ɼ�����-1�˳�: ";
//			newGrade = RegetupdateProjectGrade();//���»�ȡnewGrade;
//			if (newGrade == -1) {
//				cout << "�ѳɹ��˳�!" << endl;//�˳�����;
//				return;
//			}
//			else {
//				updateProjectGrade(project, newGrade);
//				return;
//			}//�����˳�,�������޸ĳɼ�;
//		}
//	}
//}
//
////�޸���Ŀ������
//int ProjectSorting::RegetupdateProjectGrade() {
//	int newGrade;
//	cin >> newGrade;
//	int s = cin.rdstate();
//	while (s) {//�ж�������Ƿ�Ϊ����;
//		cin.clear();
//		cerr << "����Ĳ�������!" << endl;
//		cout << "�����������-1�˳�: ";
//		while (cin.get() != '\n');
//		cin >> newGrade;
//		s = cin.rdstate();//�ж�������Ƿ�Ϊ����;
//	}
//	return newGrade;
//}
//
////�����Ŀ;
//void  ProjectSorting::AddProjects(std::vector<Project>& projects, Project& project) {
//	auto it = find_if(projects.begin(), projects.end(), [&project](Project& a)->bool {
//		return (a.name == project.name) && (a.type == project.type);
//		});
//	if (it != projects.end()) {
//		cout << "�Ѵ��ڸ���Ŀ!" << endl;
//		if (it->grade != project.grade) {
//			cout << "������Ŀ�ĳɼ����Ѵ��ڵ���Ŀ�ɼ���ͬ,�Ƿ��޸�(����1��ʾ��,����2��ʾ��,����0��ʾ�˳�����;)";
//			int a = Select1or2or0();
//			if (a == 1)
//				it->grade = project.grade;
//			else
//				return;
//		}
//	}
//}
//
////ɾ����Ŀ;
//void ProjectSorting::DeleteProjects(std::vector<Project>& projects, Project& project) {
//	auto it = find(projects.begin(), projects.end(), project);
//	if (it != projects.end()) {
//		projects.erase(it);//ɾ������Ŀ;
//	}
//	else {//δ�ҵ�ɾ����Ŀ;
//		cerr << "δ�ҵ�����Ŀ!" << endl;
//		cout << "ɾ������Ŀȷ����:" << endl
//			<< "name: " << project.name << endl
//			<< "type: " << project.type << endl
//			<< "grade: " << project.grade << endl;
//		cout << "��ѡ��:" << endl;
//		cout << "1:ִ�в��Ҳ���,�鿴��֪��Ŀ�Ƿ�������Ϊ" << project.name << "����Ŀ" << endl
//			<< "2:ִ���޸Ĳ���,�޸�����ɾ������Ŀ" << endl
//			<< "0:�˳�����";
//		int a = Select1or2or0();//�û�ѡ��;
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
	//��ʼ�����ݿ�
	mysql_init(&mysql);
	//�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
	//�������ݿ�
	//������Ҫ�����Լ��ı����������룬��ȫΪĬ�ϣ�ֻ�����*��Ϊ�Լ��������Լ���xsgl�����ĳ��Լ����������ݿ⼴��
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "test", 3306, NULL, 0) == NULL) {
		printf("����ԭ��: %s\n", mysql_error(&mysql));
		printf("����ʧ�ܣ�\n");
		exit(-1);
	}
	string sql = "CREATE TABLE IF NOT EXISTS users(\
		username VARCHAR(20) NOT NULL,\
		hashed_password VARCHAR(128) NOT NULL,\
		salt VARCHAR(100) NOT NULL,\
		PRIMARY KEY(username)\
	)";

	int re = mysql_query(&mysql, sql.c_str());
	//����projects��backup_projects�ı�;
	sql = "CREATE TABLE IF NOT EXISTS projects( \
         name varchar(100),\
		 type varchar(100),\
		 grade varchar(10),\
         path  varchar(100),\
		 user_name varchar(20),\
		 FOREIGN KEY(user_name) REFERENCES users(username)\
		 ) ";
	re = mysql_query(&mysql, sql.c_str());//���ַ�������const char*
	if (re != 0)
	{
		//std::cout << "��ʼ��ʧ��" << mysql_error(&mysql) << end
		return;
	}

	//����backup_projects;���ڱ�������;
	sql = "CREATE TABLE IF NOT EXISTS backup_projects ( \
           name varchar(100),\
		   type varchar(100),\
		   grade varchar(10),\
           path  varchar(100),\
		   user_name varchar(20)\
		   )  ";
	re = mysql_query(&mysql, sql.c_str());//���ַ�������const char*
	if (re != 0)
	{
		//std::cout << "��ʼ��ʧ��!" << mysql_error(&mysql) << endl;
		return;
	}
}

//��mysql������д�뵽Projects��;
void ProjectMysql::OutputProject(vector<Project>& projects) {
	string sql = "select * from projects where user_name=123;";
	int ret = mysql_query(&mysql, sql.c_str());
	// ��ȡ�����
	MYSQL_RES* res = mysql_store_result(&mysql);
	// ��������Ϊ�գ���ֱ�ӷ���
	if (res == NULL) {
		return;
	}
	while (MYSQL_ROW row = mysql_fetch_row(res)) {
		string s1 = row[0]; // ֱ��ʹ���ַ���
		string s2 = row[1]; // ֱ��ʹ���ַ���
		string s3 = row[2]; // ֱ��ʹ���ַ���
		string s4 = row[3]; // ֱ��ʹ���ַ���
		Project project(s1, s2, s3, s4);
		projects.push_back(project);
	}
	mysql_free_result(res); // �ͷŽ�����ڴ�

	//��ʣ�����ݿ�����backup_projects;
	mysql_query(&mysql, "truncate table bacup_projects ");
	//��projects�е����ݰ�name_user������������;
	sql = "insert into backup_projects select * from projects where user_name!=123 oder by name_user;";
	mysql_query(&mysql, sql.c_str());

}

void  ProjectMysql::InputProject(vector<Project>& projects) {
	//д������;
	string sql;
	mysql_query(&mysql, "truncate table projects ");
	vector <Project>::iterator project = projects.begin();
	while (project != projects.end()) {
		string str = "insert  into  projects  values('" + project->name + "' ,'" + project->type + "', '" + project->grade + "','" + project->path + "',123);";
		mysql_query(&mysql, str.c_str());
		//qDebug() << project->name;
		project++;
	}

	//�������е�����д�뵽projects��;
	sql = "INSERT INTO projects\
	SELECT* FROM backup_projects\
		WHERE NOT EXISTS(\
			SELECT 1 FROM projects\
			WHERE projects.user_name = backup_projects.user_name\
		); ";
	mysql_query(&mysql, sql.c_str());
	mysql_query(&mysql, "truncate table backup_projects ");
}

//ȥ����Ŀ;����ÿ�����͵���߳ɼ�;
void ProjectSorting::deduplicateByTypeAndGrade(std::vector<Project>& projects) {
	sort(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
		return a > b;
		});//lambda������sort����ѡ��;
	projects.erase(unique(projects.begin(), projects.end(), [](Project& a, Project& b)->bool {
		return a == b;
		}), projects.end());//lambda������erase����ȥ��;
}