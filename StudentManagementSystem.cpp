#include <iostream>
#include <fstream>
using namespace std;

/*
*****************************************************************************************************
                                STUDENT RECORD MANAGMENT SYSTEM
*****************************************************************************************************
*/

//  DECLARATIONS OF ALL THE FUNCTIONS USED IN THE PROGRAM

void menu();

int getwhattheywant();

int input_int_from_user();
double input_double_from_user();

void writing_in_file();
void write_trash_file();

char **regrow2(char **StudentName, int row);
double **regrow(double **data, int &row);
void add(double *arr, char *name, double **data, int row, int checkrow, ofstream &fout);

void search_by_rollno(double **data, char **name, int row, int col);

int search_for_record_to_delete(double **data, int row);
void file_update(double **arr, char **name, int row);

void update_a_record(double *data, double **check, int row, char *name, int key);
void update_rollno(double *data, double **check, int key, int row);
void update_name(char *name);
void update_assignment(double *data);
void update_quiz(double *data);
void update_mids(double *data);
void update_cgpa(double *data);

void copyarr(char** &newarr, char** &StudentName, int row, int key);
void copyarr_double(int delete_a_row, int row, double** &temp, double** &data);
char** dlt_a_charrecord(int delete_a_row, char** &StudentName, int row);
double** dlt_a_datarecord(int delete_a_row, double** &data, int &row);
void create_trash_file(double *arr, char *name);

void show_detail(double* data, char* name);

void HighestCGPA(double **data, char **name, int row, int col);

void LowestCGPA(double **data, char **name, int row, int col);

void marks_less_than_50(double **data, char **name, int row, int col);

void read_from_file(ifstream &fin);
void read_from_trashfile(ifstream &fin);

void delete_memory(double **data, char **StudentName, int row);

// MAIN FUNCTION

int main()
{
	double **data = NULL;
	char **StudentName = NULL;
	int row = 0, col = 13;
    ofstream fout;

	writing_in_file();
	write_trash_file();

	cout << endl;
	cout << "----------------------------------WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM------------------------------" << endl;
	cout << endl;

	menu();
	int whattheywant = getwhattheywant();


	while (whattheywant != 10)
	{
		switch (whattheywant)
		{
		case 1:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 01                                            " << endl;
            cout << "                                             ~ADD A NEW RECORD~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			StudentName = regrow2(StudentName, row);
			data = regrow(data, row);
			add(data[row - 1], StudentName[row - 1], data, row, row - 1, fout);
			break;
		}

		case 2:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 02                                           " << endl;
            cout << "                                        ~SEARCH A RECORD BY ROLL NUMBER~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			search_by_rollno(data, StudentName, row, 0);
			break;
		}

		case 3:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 03                                            " << endl;
            cout << "                                           ~TOTAL NUMBER OF STUDENTS~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			cout << "Total Number of Students are: " << row << endl;
			break;
		}

		case 4:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 04                                            " << endl;
            cout << "                                            ~UPDATE A STUDENT RECORD~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			int row_to_update = search_for_record_to_delete(data, row);
			if (row_to_update != -1)
			{
				update_a_record(data[row_to_update], data, row, StudentName[row_to_update], row_to_update);
				file_update(data, StudentName, row);
				cout << "RECORD UPDATED SUCCESSFULLY!" << endl;
			}
			break;
		}

		case 5:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 05                                            " << endl;
            cout << "                                           ~DELETE A STUDENT RECORD~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			int row_to_delete = search_for_record_to_delete(data, row);
			if (row_to_delete != -1)
			{
				create_trash_file(data[row_to_delete], StudentName[row_to_delete]);
				StudentName = dlt_a_charrecord(row_to_delete, StudentName, row);
				data = dlt_a_datarecord(row_to_delete, data, row);
				file_update(data, StudentName, row);
				cout << "RECORD DELETED SUCCESSFULLY!" << endl;
			}
			break;
		}

		case 6:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 06                                            " << endl;
            cout << "                                   ~SHOW A STUDENT RECORD WITH THE HIGHEST CGPA~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			HighestCGPA(data, StudentName, row, 12);
			break;
		}

		case 7:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 07                                            " << endl;
            cout << "                                   ~SHOW A STUDENT RECORD WITH THE LOWEST CGPA~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			LowestCGPA(data, StudentName, row, 12);
			break;
		}

		case 8:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 08                                            " << endl;
            cout << "                                    ~SHOW STUDENTS WITH MIDTERM MARKS LESS THAN 50~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			marks_less_than_50(data, StudentName, row, 11);
			break;
		}

		case 9:
		{
            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 09                                            " << endl;
            cout << "                                      ~SHOW ALL THE RECORD FROM THE FILE~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;
			char select;
			cout << "Which file do you want to see?" << endl;
			cout << "            *TYPE 'A' TO VIEW COMPLETE RECORD FROM THE FILE StudentRecordSystem.txt" << endl;
			cout << "            *TYPE 'T' TO VIEW DELETED RECORD FROM THE FILE TrashBin.txt" << endl;
			cout << "SELECT YOUR PREFERENCE: ";
			cin >> select;

			while (true)
			{
                if(select=='t'||select=='T')
                {
                	ifstream fin;
					read_from_trashfile(fin);
					break;
                }

                else if(select=='a'||select=='A')
                {
                	ifstream fin;
					read_from_file(fin);
					break;
                }

                else
                {
                    cout << "INVALID OPTION!!!" << endl;
                }
		
                cout << "TRY AGAIN, SELECT YOUR PREFERENCE: ";
				cin >> select;
			}
			break;
		}

		default:
		{
			cout << "INVALID INPUT!!!" << endl;
			break;
		}
		}
		menu();
		whattheywant = getwhattheywant();
	}

	delete_memory(data, StudentName, row);

            cout << "***********************************************************************************************************" << endl;
            cout << "                                             SELECTED OPTION 10                                            " << endl;
            cout << "                                                   ~EXIT~                                            " << endl;
            cout << "***********************************************************************************************************" << endl;

	cout << "Exiting..." << endl;

	cout << endl;
	system("pause");
	return 0;
}//end of main

//  Function to display menu to the user so that he/she can select his/her prefrence easily
void menu()
{
	cout << endl;
    cout << "___________________________________________________________________________________________________________" << endl;
	cout << "                                               MAIN MENU                                                   " << endl;
	cout << "                                 (Note = Kindly select from following options.)                            " << endl;
    cout << "___________________________________________________________________________________________________________" << endl;
	cout << endl;
	cout << "                           1- Add a new record.                                                            " << endl;
	cout << "                           2- Search a student record by Roll Number.                                      " << endl;
	cout << "                           3- View total number of students.                                               " << endl;
	cout << "                           4- Update a student record.                                                     " << endl;
	cout << "                           5- Delete a student record.                                                     " << endl;
	cout << "                           6- Show students with highest CGPA.                                             " << endl;
	cout << "                           7- Show students with lowest CGPA.                                              " << endl;
	cout << "                           8- Show students with mid-term marks less than 50.                              " << endl;
	cout << "                           9- Show record from the file.                                                   " << endl;
	cout << "                          10- Exit.                                                                        " << endl;
    cout << "___________________________________________________________________________________________________________" << endl;
	cout << endl;
}// end of main menu

//  Function to ask user to select his/her desired option the main menu
int getwhattheywant()
{
	cout << endl;
	int opt;
	cout << "ENTER YOUR DESIRED OPTION= ";
	opt = input_int_from_user();
	cout << endl;
	return opt;
}// end of getwhattheywant

// Buffers input taken from the user

int input_int_from_user()
{
	int num;
	while (!(cin>>num))
	{
		cout<<"ERROR, Enter again: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return num;	
}// end of input_int_from_user
double input_double_from_user()
{
	double num;
	while (!(cin>>num))
	{
		cout<<"ERROR, Enter again: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	return num;	
}// end of input_double_from_user

//  Function to create file to store student record on hard drive

//  Function to create file named StudentRecordSystem.txt
void writing_in_file()
{
	ofstream fout;
	fout.open("StudentRecordSystem.txt");

	fout << "----------------------------------WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM------------------------------" << endl;
	fout << endl;
	fout << "___________________________________________________________________________________________________________" << endl;
	fout << "|     | Personal Information  |       ASSIGNMENTS      |        QUIZZES         |    Marks      | GRADES  |" << endl;

	fout << "___________________________________________________________________________________________________________" << endl;
	fout << "| R#  | Student Complete Name | A1 | A2 | A3 | A4 | A5 | Q1 | Q2 | Q3 | Q4 | Q5 | Midterm Marks | CGPA    |" << endl;
	fout << "___________________________________________________________________________________________________________" << endl;
	fout << endl;
	fout.close();
}// end of writing_in_file  

//  Function to create file named TrashBin.txt to store deleted record
void write_trash_file()
{
	ofstream f2;
	f2.open("TrashBin.txt");

	f2 << "----------------------------------WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM------------------------------" << endl;
	f2 << endl;
	f2 << "___________________________________________________________________________________________________________" << endl;
	f2 << "|     | Personal Information  |       ASSIGNMENTS      |        QUIZZES         |    Marks      | GRADES  |" << endl;

	f2 << "___________________________________________________________________________________________________________" << endl;
	f2 << "| R#  | Student Complete Name | A1 | A2 | A3 | A4 | A5 | Q1 | Q2 | Q3 | Q4 | Q5 | Midterm Marks | CGPA    |" << endl;
	f2 << "___________________________________________________________________________________________________________" << endl;
	f2 << endl;
	f2.close();
}// end of write_trash_file

//  OPTION 01 = ADD A NEW RECORD

char **regrow2(char **StudentName, int row)
{
	if (row == 0)
	{
		char **temp = NULL;
		temp = new char *[row + 1];

		for (int i = 0; i < row + 1; i++)
		{
			temp[i] = new char[35];
		}

		StudentName = NULL;

		return temp;
	}

	else
	{
		char **temp = NULL;
		temp = new char *[row + 1];
		for (int i = 0; i < row + 1; i++)
		{
			temp[i] = new char[35];
		}

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 35; j++)
			{
				temp[i][j] = StudentName[i][j];
			}
		}

		for (int i = 0; i < row; i++)
		{
			delete[] StudentName[i];
		}
		delete[] StudentName;
		StudentName = NULL;
		return temp;
	}
}// end of regrow2

double **regrow(double **data, int &row)
{
	if (row == 0)
	{
		double **temp = NULL;
		temp = new double *[row + 1];
		for (int i = 0; i < row + 1; i++)
		{
			temp[i] = new double[13];
		}
		data = NULL;
		row++;
		return temp;
	}
	else
	{
		double **temp = NULL;
		temp = new double *[row + 1];
		for (int i = 0; i < row + 1; i++)
		{
			temp[i] = new double[13];
		}
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				temp[i][j] = data[i][j];
			}
		}

		for (int i = 0; i < row; i++)
		{
			delete[] data[i];
		}
		delete[] data;
		data = NULL;
		row++;
		return temp;
	}
}// end of regrow

void add(double *arr, char *name, double **data, int row, int checkrow, ofstream &fout)
{
	int num;
	cout << "Enter student roll number = ";
	arr[0] = input_double_from_user();

	int flag = 1;

	for (int i = 0; i < row; i++)
	{
		if (i != checkrow)
		{
			if (data[i][0] == arr[0])
			{
				flag = 0;
			}
		}
	}

	while (flag == 0)
	{
		cout << "ROLL NUMBER ALREADY EXISTS!!!" << endl;
		cout << "TRY AGAIN, Enter student roll number = ";
		arr[0] = input_double_from_user();

		flag = 1;

		for (int i = 0; i < row; i++)
		{
			if (i != checkrow)
			{
				if (data[i][0] == arr[0])
				{
					flag = 0;
				}
			}
		}
	}

	cin.ignore();
	cout << "Enter Student Name: ";
	cin.getline(name, 35);

	cout << "HOW MANY ASSIGNMENTS YOU WANT TO ADD? ";
	num = input_int_from_user();

	while (num > 5)
	{
		cout << "Only 5 Assignments are allowed." << endl;
		cout << "TRY AGAIN, HOW MANY ASSIGNMENTS YOU WANT TO ADD? ";
		num = input_int_from_user();
	}

	for (int i = 1; i <= 5; i++)
	{
		arr[i] = -1;
	}

	for (int i = 1; i <= 5 && i <= num; i++)
	{
		cout << "Enter student assignment " << i << " marks = ";
		arr[i] = input_double_from_user();
		if (arr[i] > 10.0 || arr[i] == -1)
		{
			cout << "MARKS CAN'T BE GREATER THAN 10." << endl;
			i--;
		}
	}

	cout << "HOW MANY QUIZZES YOU WANT TO ADD? ";
	num = input_int_from_user();

	while (num > 5)
	{
		cout << "Only 5 Quizzes are allowed." << endl;
		cout << "TRY AGAIN, HOW MANY QUIZZES YOU WANT TO ADD? ";
    	num = input_int_from_user();
	}

	for (int i = 6; i <= 10; i++)
	{
		arr[i] = -1;
	}

	for (int i = 6; i <= 10 && i - 5 <= num; i++)
	{
		cout << "Enter student quiz " << i - 5 << " marks = ";
		arr[i] = input_double_from_user();
		if (arr[i] > 10.0 || arr[i] == -1)
		{
			cout << "MARKS CAN'T BE GREATER THAN 10." << endl;
			i--;
		}
	}

	cout << "Enter student midterm marks = ";
	arr[11] = input_double_from_user();
	while (arr[11] > 100.00)
	{
		cout << "MARKS CAN'T BE GREATER THAN 100." << endl;
		cout << "Please again enter student midterm marks = ";
	    arr[11] = input_double_from_user();
	}

	cout << "Enter student CGPA = ";
	arr[12] = input_double_from_user();
	while (arr[12] > 4.0)
	{
		cout << "CGPA CAN'T BE GREATER THAN 4.0 ." << endl;
		cout << "Please again enter student CGPA = ";
		arr[12] = input_double_from_user();
	}

	fout.open("StudentRecordSystem.txt", ios::app);
	fout << "| " << arr[0] << "  | " << name << "           |  " << arr[1] << " | " << arr[2] << "  | " << arr[3] << " | " << arr[4] << " | " << arr[5] << " | " << arr[6] << "  |  " << arr[7] << " | " << arr[8] << "  | " << arr[9] << "  | " << arr[10] << "  |      " << arr[11] << "       |  " << arr[12] << "    |" << endl;
	fout << "___________________________________________________________________________________________________________" << endl;
	fout << endl;
	fout.close();

	cout << "INFORMATION ADDED SUCCESSFULLY!!!" << endl;
}// end of add

//  OPTION 02 = SEARCH A STUDENT RECORD BY ROLL NUMBER.

void search_by_rollno(double **data, char **name, int row, int col)
{
	if (row == 0)
	{
		cout << "NO INFORMATION HAS ADDED YET." << endl;
	}
	else
	{
		int search;
		cout << "ENTER ROLL NUMBER TO SEARCH: ";
		search = input_int_from_user();
		int flag = 0;
		while (flag == 0)
		{
			for (int i = 0; i < row; i++)
			{
				if (data[i][col] == search)
				{
					flag = 1;
				}
			}
			if (flag == 0)
			{
				char opt = 'y';
				cout << "ROLL NUMBER DOESN'T EXIST!!!" << endl;
				cout << "Do you want to search again [y/n]: " << endl;
				cin >> opt;
				if (opt == 'y' || opt == 'Y')
				{
					flag = 0;
					cout << "ENTER ROLL NUMBER AGAIN TO SEARCH: ";
					search = input_int_from_user();
				}
				else
				{
					flag = -1;
				}
			}
		}
		if (flag == 1)
		{
			for (int i = 0; i < row; i++)
			{
				if (data[i][col] == search)
				{
					show_detail(data[i], name[i]);
				}
			}
		}
	}
}// end of search_by_rollno

//  Common function used in both update and delete option

//  Function to update record in the file after updation or deletion
void file_update(double **arr, char **name, int row)
{
	ofstream f1;
	f1.open("StudentRecordSystem.txt");

	f1 << "----------------------------------WELCOME TO STUDENT RECORD MANAGEMENT SYSTEM------------------------------" << endl;
	f1 << endl;
	f1 << "___________________________________________________________________________________________________________" << endl;
	f1 << "|     | Personal Information  |       ASSIGNMENTS      |        QUIZZES         |    Marks      | GRADES  |" << endl;

	f1 << "___________________________________________________________________________________________________________" << endl;
	f1 << "| R#  | Student Complete Name | A1 | A2 | A3 | A4 | A5 | Q1 | Q2 | Q3 | Q4 | Q5 | Midterm Marks | CGPA    |" << endl;
	f1 << "___________________________________________________________________________________________________________" << endl;
	f1 << endl;
	int j = 0;
	for (int i = 0; i < row; i++)
	{
		j = 0;
     	f1 << "| " << arr[i][0] << "  | ";
		while(name[i][j]!= '\0')
		{
			f1 << name[i][j];
			j++;
		}
		f1 << "           |  " << arr[i][1] << " | " << arr[i][2] << "  | " << arr[i][3] << " | " << arr[i][4] << " | " << arr[i][5] << " | " << arr[i][6] << "  |  " << arr[i][7] << " | " << arr[i][8] << "  | " << arr[i][9] << "  | " << arr[i][10] << "  |      " << arr[i][11] << "       |  " << arr[i][12] << "    |" << endl;
	    f1 << "___________________________________________________________________________________________________________" << endl;
    }

	f1 << endl;
	f1.close();
}//end of file_update
//  Function to search for the roll number to search and delete
int search_for_record_to_delete(double **data, int row)
{
	if (row == 0)
	{
		cout << "NO INFORMATION HAS ADDED YET." << endl;
		return -1;
	}
	else
	{
		int search;
		cout << "ENTER STUDENT ROLL NUMBER: ";
		search = input_int_from_user();
		int flag = 0;
		while (flag == 0)
		{
			for (int i = 0; i < row; i++)
			{
				if (data[i][0] == search)
				{
					return i;
				}
			}
			if (flag == 0)
			{
				char opt = 'y';
				cout << "ROLL NUMBER DOESN'T EXIST!!!" << endl;
				cout << "Do you want to search again [y/n]: " << endl;
				cin >> opt;
				if (opt == 'y' || opt == 'Y')
				{
					flag = 0;
					cout << "ENTER ROLL NUMBER AGAIN TO SEARCH: ";
					search = input_int_from_user();
				}
				else
				{
					return -1;
				}
			}
		}
	}
}// end of search_for_record_to_delete

//  OPTION 04 = UPDATE A STUDENT RECORD.

void update_a_record(double *data, double **check, int row, char *name, int key)
{
	cout << "    WHAT DO YOU WANT TO UPDATE?" << endl;
	cout << "          * TYPE R TO UPDATE STUDENT ROLL NUMBER." << endl;
	cout << "          * TYPE N TO UPDATE STUDENT NAME." << endl;
	cout << "          * TYPE A TO UPDATE STUDENT ASSIGNMENT MARKS." << endl;
	cout << "          * TYPE Q TO UPDATE STUDENT QUIZ MARKS." << endl;
	cout << "          * TYPE M TO UPDATE STUDENT MIDTERM MARKS." << endl;
	cout << "          * TYPE C TO UPDATE STUDENT CGPA." << endl;
	cout << "          * TYPE U TO UPDATE A STUDENT COMPLETE RECORD." << endl;

	char select;
	cout << "SELECT YOUR PREFERENCE: ";
	cin >> select;
	int flag = 1;

	while (flag == 1)
	{
		switch (select)
		{
		case 'r':
		{
			update_rollno(data, check, key, row);
			flag = 0;
			break;
		}

		case 'R':
		{
			update_rollno(data, check, key, row);
			flag = 0;
			break;
		}

		case 'n':
		{
			update_name(name);
			flag = 0;
			break;
		}

		case 'N':
		{
			update_name(name);
			flag = 0;
			break;
		}

		case 'a':
		{
			update_assignment(data);
			flag = 0;
			break;
		}

		case 'A':
		{
			update_assignment(data);
			flag = 0;
			break;
		}

		case 'Q':
		{
			update_quiz(data);
			flag = 0;
			break;
		}

		case 'q':
		{
			update_quiz(data);
			flag = 0;
			break;
		}

		case 'm':
		{
			update_mids(data);
			flag = 0;
			break;
		}

		case 'M':
		{
			update_mids(data);
			flag = 0;
			break;
		}

		case 'C':
		{
			update_cgpa(data);
			flag = 0;
			break;
		}

		case 'c':
		{
			update_cgpa(data);
			flag = 0;
			break;
		}

		case 'U':
		{
			update_rollno(data, check, key, row);
			update_name(name);
			update_assignment(data);
			update_quiz(data);
			update_mids(data);
			update_cgpa(data);
			flag = 0;
			break;
		}

		case 'u':
		{
			update_rollno(data, check, key, row);
			update_name(name);
			update_assignment(data);
			update_quiz(data);
			update_mids(data);
			update_cgpa(data);
			flag = 0;
			break;
		}

		default:
		{
			flag = 1;
			cout << "INVALID INPUT!!!" << endl;
			break;
		}
		}

        if(flag == 1)
        {
            cout << "TRY AGAIN, SELECT YOUR PREFERENCE: ";
			cin >> select;
        }
	}
}// end of update_a_record
//  Function to update student roll number
void update_rollno(double *data, double **check, int key, int row)
{
	cout << "ENTER UPDATED ROLL NUMBER = ";
	data[0] = input_double_from_user();

	int flag = 1;

	for (int i = 0; i < row; i++)
	{
		if (i != key)
		{
			if (check[i][0] == data[0])
			{
				flag = 0;
			}
		}
	}

	while (flag == 0)
	{
		cout << "ROLL NUMBER ALREADY EXISTS!!!" << endl;
		cout << "TRY AGAIN, ENTER UPDATED ROLL NUMBER = ";
		data[0] = input_double_from_user();

		flag = 1;

		for (int i = 0; i < row; i++)
		{
			if (i != key)
			{
				if (check[i][0] == data[0])
				{
					flag = 0;
				}
			}
		}
	}
}// end of update_rollno
//  Function to update student name
void update_name(char *name)
{
	cin.ignore();
	cout << "ENTER STUDENT UPDATED NAME: ";
	cin.getline(name, 35);
}// end of update_name
//  Function to update student assignment marks
void update_assignment(double *data)
{
	for (int i = 1; i < 5; i++)
	{
		if (data[i] != -1)
		{
			cout << "ENTER UPDATED ASSIGNMENT " << i << " MARKS: ";
			data[i] = input_double_from_user();

			if (data[i] > 10 || data[i] < 0)
			{
				cout << "Marks can't be greater than 10." << endl;
				i--;
			}
		}
	}
}// end of update_assignment
//  Function to update student quiz marks
void update_quiz(double *data)
{
	for (int i = 6; i < 10; i++)
	{
		if (data[i] != -1)
		{
			cout << "ENTER UPDATED QUIZ " << i-5 << " MARKS: ";
			data[i] = input_double_from_user();

			if (data[i] > 10 || data[i] < 0)
			{
				cout << "Marks can't be greater than 10." << endl;
				i--;
			}
		}
	}
}// end of update_quiz
//  Function to update student midterm marks
void update_mids(double *data)
{
	int flag = 0;
	cout << "ENTER UPDATED MIDTERM MARKS: ";
	data[11] = input_double_from_user();

	while (flag == 0)
	{
		if (data[11] > 100 || data[11] < 0)
		{
			cout << "Marks can't be greater than 100." << endl;
			cout << "ENTER AGAIN UPDATED MIDTERM MARKS: ";
			data[11] = input_double_from_user();
			flag = 0;
		}

		else
		{
			flag = 1;
		}
	}
}// end of update_mids
//  Function to update student CGPA
void update_cgpa(double *data)
{
	int flag = 0;
	cout << "ENTER UPDATED CGPA: ";
	data[12] = input_double_from_user();

	while (flag == 0)
	{
		if (data[12] > 4.0 || data[12] < 0.0)
		{
			cout << "CGPA can't be greater than 4.0." << endl;
			cout << "ENTER AGAIN UPDATED CGPA: ";
			data[12] = input_double_from_user();
			flag = 0;
		}

		else
		{
			flag = 1;
		}
	}
}// end of update_cgpa

//  OPTION 05 = DELETE A STUDENT RECORD.

//  2D CHARACTER ARRAY SHRINK CODE

void copyarr(char**& newarr, char** &StudentName, int row, int key)
{
	int j=0;
	for (int i = 0; i < row; i++)
	{
		if (i != key)
		{
			for(int k = 0; k<35 && StudentName[i][k] != '\0'; k++)
			{
				newarr[j][k] = StudentName[i][k];
			}
			j++;
		}
	}
}// end of copyarr

char** dlt_a_charrecord(int row_to_delete, char** &StudentName, int row)
{
	char** newarr = NULL;
	newarr = new char*[row-1];


	for (int i = 0; i < row - 1; i++)
	{
		newarr[i] = new char[35];
	}

	copyarr(newarr, StudentName, row, row_to_delete);

	for (int i = 0; i < row; i++)
	{
		delete[] StudentName[i];
	}
	delete[] StudentName;
	StudentName = NULL;

	return newarr;
}// end of delete_a_charrecord

void copyarr_double(int delete_a_row, int row, double** &temp, double** &data)
{
	int k=0;
	for (int i = 0; i < row; i++)
	{
		if (i != delete_a_row)
		{
			for (int j = 0; j < 13; j++)
			{
				temp[k][j] = data[i][j];
			}
			k++;
		}
	}

}

//  2D DATA ARRAY SHRINK CODE
double** dlt_a_datarecord(int delete_a_row, double** &data, int &row)
{
	double** temp = NULL;
	temp = new double*[row-1];

	for (int i = 0; i < row - 1; i++)
	{
		temp[i] = new double[13];
	}

	copyarr_double(delete_a_row, row, temp, data);

	for (int i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
	data = NULL;
	row--;
	return temp;
}// end of dlt_a_datarecord

void create_trash_file(double *arr, char *name)
{
	ofstream f2;
	f2.open("TrashBin.txt", ios::app);

	f2 << "| " << arr[0] << "  | " << name << "           |  " << arr[1] << " | " << arr[2] << "  | " << arr[3] << " | " << arr[4] << " | " << arr[5] << " | " << arr[6] << "  |  " << arr[7] << " | " << arr[8] << "  | " << arr[9] << "  | " << arr[10] << "  |      " << arr[11] << "       |  " << arr[12] << "    |" << endl;
	f2 << "___________________________________________________________________________________________________________" << endl;
	f2 << endl;
	f2.close();
}// end of create_trash_file

//  Function to display all the details of students [THIS FUNCTION IS USED IN OPTION 6, 7, 8]
void show_detail(double* data, char* name)
{
	cout << endl;
	cout << "     * STUDENT NAME = " << name << endl;
	cout << "     * STUDENT ROLL NUMBER = " << data[0] << endl;
	cout << "     * Student Assignments marks:" << endl;
	for (int j = 1; j <= 5; j++)
	{
		if (data[j] != -1)
			{
				cout << "        * Assignment " << j << " marks = " << data[j] << endl;
			}
	}
	cout << "     * Student Quiz marks:" << endl;
	for (int j = 6; j <= 10; j++)
	{
		if (data[j] != -1)
		{
			cout << "        * Quiz " << j - 5 << " marks = " << data[j] << endl;
		}
	}
	cout << "     * STUDENT MIDTERM MARKS = " << data[11] << endl;
	cout << "     * STUDENT CCGPA = " << data[12] << endl;
	cout << endl;

}// end of show_detail

//  OPTION 06 = SHOW STUDENT WITH THE HIGHEST CGPA.

void HighestCGPA(double **data, char **name, int row, int col)
{
	if (row == 0)
	{
		cout << "NO INFORMATION HAS ADDED YET." << endl;
	}
	else
	{
		double max = data[0][col];
		int count = 0;
		for (int i = 0; i < row; i++)
		{
			if (max < data[i][col])
			{
				max = data[i][col];
			}
		}

		for (int i = 0; i < row; i++)
		{
			if (max == data[i][col])
			{
				count++;
			}
		}


		cout << "HIGHEST CGPA is = " << max << endl;
		cout << "TOTAL STUDENTS WITH THE HIGHEST CGPA are = " << count << endl;
		char opt;
		cout << "Do you want to the details of student with Highest CGPA [y/n]:" << endl;
		cin >> opt;
		if (opt == 'y' || opt == 'Y')
		{
			cout << endl;
			cout << "Details of students with the Highest CGPA:" << endl;
			for (int i = 0; i < row; i++)
			{
				if (data[i][12] == max)
				{
                    show_detail(data[i], name[i]);
				}
			}
		}
		else
		{
			cout << "Directing You Back to The Main Menu." << endl;
		}
	}
}// end of HighestCGPA

//  OPTION 07 = SHOW STUDENT WITH THE LOWEST CGPA.

void LowestCGPA(double **data, char **name, int row, int col)
{
	if (row == 0)
	{
		cout << "NO INFORMATION HAS ADDED YET." << endl;
	}
	else
	{
		double min = data[0][col];
		int count = 0;
		for (int i = 0; i < row; i++)
		{
			if (min > data[i][col])
			{
				min = data[i][col];
			}
		}

		for (int i = 0; i < row; i++)
		{
			if (min == data[i][col])
			{
				count++;
			}
		}
		cout << "LOWEST CGPA is = " << min << endl;
		cout << "TOTAL STUDENTS WITH THE LOWEST CGPA are = " << count << endl;
		char opt;
		cout << "Do you want to the details of student with Lowest CGPA [y/n]:" << endl;
		cin >> opt;
		if (opt == 'y' || opt == 'Y')
		{
			cout << endl;
			cout << "Details of student with the lowest CGPA:" << endl;
			for (int i = 0; i < row; i++)
			{
				if (data[i][12] == min)
				{
                    show_detail(data[i], name[i]);
                }

			}
		}
		else
		{
			cout << "Directing You Back to The Main Menu." << endl;
		}
	}
}// end of LowestCGPA

//  OPTION 08 = SHOW STUDENT WITH MIDTERM MARKS LESS THAN 50.

void marks_less_than_50(double **data, char **name, int row, int col)
{
	if (row == 0)
	{
		cout << "NO INFORMATION HAS ADDED YET." << endl;
	}
	else
	{
        int mark=0;
		for (int i = 0; i < row; i++)
		{
			cout << endl;
			cout << "Details of student with the MidTerm Marks less than 50:" << endl;
			cout << endl;
			if (data[i][col] < 50)
            {
                mark=0;
                show_detail(data[i], name[i]);
			}
		}

        if(mark==1)
        {
            cout<<"NO RECORD FOUND!!!"<<endl;
        }
	}
}// end of marks_less_than_50

//  OPTION 09 = SHOW RECORD FROM THE FILE.

void read_from_file(ifstream &fin)
{
	char read;
	fin.open("StudentRecordSystem.txt", ios::in);

	while (!fin.eof())
	{
		fin.get(read);
		cout << read;
	}

	fin.close();
}// end of read_from_file

void read_from_trashfile(ifstream &fin)
{
	char read;
	fin.open("TrashBin.txt", ios::in);

	while (!fin.eof())
	{
		fin.get(read);
		cout << read;
	}

	fin.close();
}// end of read_from_trashfile

//  Function to erase all the allocated memory in heap at the end

void delete_memory(double **data, char **StudentName, int row)
{
	for (int i = 0; i < row; i++)
	{
		delete[] StudentName[i];
	}
	delete[] StudentName;
	StudentName = NULL;

	for (int i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
	data = NULL;
}// end of delete_memory