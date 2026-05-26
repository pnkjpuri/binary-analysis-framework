#ifndef FRAMEWORK_H
#define FRAMEWORK_H

/* ==============================
   AUTHENTICATION
============================== */

void registerUser();
void loginUser();
void adminLogin();

int validatePassword(char password[]);
void inputPassword(char password[]);

/* ==============================
   PANELS
============================== */

void adminPanel(int id, char name[]);
void userPanel(int id, char name[]);

/* ==============================
   ADMIN FUNCTIONS
============================== */

void viewUsers();
void makeAdmin();
void deleteUser();

void readFile();
void modifyFile();
void deleteFile();

void viewReports();
void viewActivityLogs();

void changeAdminPassword();

/* ==============================
   USER FUNCTIONS
============================== */

void myProfile(int id);
void uploadAndAnalyzeFile(int id,
                           char name[]);

/* ==============================
   BINARY ANALYSIS
============================== */

void fileInfo(const char *filename);
void hexDump(const char *filename);
void extractStrings(const char *filename);
void patternScan(const char *filename);
void fullAnalysis(const char *filename);

/* ==============================
   LOGGING
============================== */

void logActivity(
    int userId,
    const char *userName,
    const char *action,
    const char *filename);

void logReport(
    int userId,
    const char *userName,
    const char *action,
    const char *filename);

#endif