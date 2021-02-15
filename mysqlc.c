#include <mysql.h>
//#include <mysql/mysql.h>
#include <stdio.h>
//#include <stdlib.h>

#include <string.h>
#define MAX_PATIENTS 100

//a structure
typedef struct Patients
{
	char patient_name[50];
	char patient_gender[50];
	char DOI[100];
	char officer_name[100];
	
} patient;
patient patients[MAX_PATIENTS];
//file
FILE *server_file;

//main function
int main(int argc, char **argv)
{

	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
	{

		exit(1);
		printf("impossible");
	}
	// //insert into
	server_file = fopen("/home/katende/Desktop/sockets_final/enroll.txt", "r");
	if (server_file == NULL)
	{
		puts("\nFiles does not exit\n");
	}
	else
	{
		char firstName[100];
		char secondName[100];
		char server_string[256];
		char store[200];
		int index = 0;
        if (mysql_real_connect(con, "127.0.0.1", "root", "", "final_project", 0, NULL, 0) == NULL)
			{
				fprintf(stderr, "%s\n", mysql_error(con));
				printf("connected\n We are connected\n");
			}
		while (fgets(server_string, 100, server_file) != NULL)
		{

			strcpy(store, server_string);
			sscanf(store, "%s %s %s %s %s", firstName, secondName,
				   patients[index].DOI, patients[index].patient_gender, patients[index].officer_name);
			strcpy(patients[index].patient_name, firstName);
			strcat(patients[index].patient_name, " ");
			strcat(patients[index].patient_name, secondName);
			printf("PatientName: %s \nGender:%s \nOfficerName:%s \nDate:%s\n", patients[index].patient_name,
				   patients[index].patient_gender,
				   patients[index].officer_name,
				   patients[index].DOI);
			char statement[200];

			snprintf(statement, 500,"INSERT INTO patients_list(PatientName,OfficerUserName, Gender ,DOI)\
			 VALUES('%s', '%s', '%s', '%s')", patients[index].patient_name, patients[index].officer_name,
			 patients[index].patient_gender, patients[index].DOI);
			
			if (mysql_query(con, statement))
			{
				//finish_with_error(con);
                fprintf(stderr, "%s\n", mysql_error(con));
				printf("\ninsertedWell\n");
			}


			index++;
		}

	}
     fclose(fopen("/home/katende/Desktop/sockets_final/enroll.txt", "w"));
	mysql_close(con);
	exit(0);
}
