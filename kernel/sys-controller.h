using namespace std;

class Root {
private:
  int password;
  bool isRootPassed = false;
public:
  string root = "root";
  bool isRootSelected = true;
  void create_root_pass();
  bool isRootSelectedTest();
  bool isRootPassedTest();
  bool writeRootPassword();
  void selectSuperUser();
};

void Root::selectSuperUser() {
    if (isRootPassed) {
        bool isPass = writeRootPassword();
        if (isPass) {
            cout << "Root selected";
        }
    }
    else {
        cout << "Root selected";
    }
}

void Root::create_root_pass(){
  cout << "Write password superuser (Integer type only!): ";
  cin >> password;
  isRootPassed = true;
  cout << "Password created!\n\n";
}

bool Root::isRootSelectedTest() {
    return isRootSelected;
}

bool Root::writeRootPassword() {
  bool isPass;
  int attempts = 3;
  int root_pass;
  cout << "Write superuser password : ";
  cin >> root_pass;
  isPass = root_pass == password;
  if(isPass){
    return true;
  }
  else {
     while(root_pass != password){
         if (attempts == 0) {
             return false;
             break;
         }
         --attempts;
         cout << "Wrong password try again (you have " << attempts << " attempts)\n\n";
         cout << "Write user password : ";
         cin >> root_pass;
         if (attempts == 0) {
             return false;
             break;
         }
         else if (root_pass == password && attempts > 0) {
             return true;
             break;
         }
     }
  }
  return true;
}

bool Root::isRootPassedTest() {
    return isRootPassed;
}

class User {
private:
    int password;
public:
    string username;
    bool isSelected = false;
    void create_user();
    bool isSelectedTest();
    bool writePassword();
};

class Language {
public:
  vector <string> language{"en_US"};
  vector <bool> languageBool;
  void setLanguage();
  void showLanguage();
};

void Language::setLanguage(){
  vector <string>::iterator languageIter;
  int i = 1;
  for (languageIter = language.begin(); languageIter != language.end() ; ++languageIter) {

    cout << i << " - " << *languageIter << endl;
  }
  int language_test;
  cout << "Write language what you want to set : ";
  cin >> language_test;
  switch (language_test) {
    case 1:
      languageBool.push_back(true);
  }
}

void Language::showLanguage(){
  vector <string>::iterator languageIter;
  for (languageIter = language.begin() ; languageIter != language.end() ; ++languageIter) {
    cout << *languageIter << endl;
  }
}

void User::create_user() {
    int selectUser;
    cout << "Write username: ";
    cin >> username;
    cout << "Write password (Integer type only!): ";
    cin >> password;
    cout << "Do you want to select the user just created?\n";
    cout << "1 - Yes\n";
    cout << "2 - No\n";
    cin >> selectUser;
    if (selectUser == 1) {
        isSelected = true;
        cout << "User selected!\n";
    } else if (selectUser == 2) {
        isSelected = false;
        cout << "User not selected!\n";
    }
    cout << "User created!\n";
}

bool User::isSelectedTest() {
    return isSelected;
}

bool User::writePassword(){
  bool isPass;
  int attempts = 3;
  int user_pass;
  cout << "Write user password : ";
  cin >> user_pass;
  isPass = user_pass == password;
  if(isPass){
    return true;
  }
  else {
     while(user_pass != password){
       if(attempts == 0){
         return false;
         break;
       }
       --attempts;
       cout << "Wrong password try again (you have " << attempts << " attempts)\n\n";
       cout << "Write user password : ";
       cin >> user_pass;
       if(attempts == 0){
         return false;
         break;
       }
       else if(user_pass == password && attempts > 0){
        return true;
        break;
       }
     }
  }
  return true;
}

void terminal() {
    bool userSel = false;
    bool canRoot = true;
    Language language;
    User user;
    Root root;
    string help[3][2] = {
      {"exit","Exit from gunix!"},
      {"echo","Show something in console"},
      {"create-user","Create user!"}
    };
    while (true) {
        if (user.isSelectedTest()) {
            userSel = true;
            canRoot = false;
            cout << user.username << "@gunix : ";
        } else {
            userSel = false;
            canRoot = true;
            cout << root.root << "@gunix : ";
        }
        string console;
        cin >> console;

        if(userSel){
          bool isPass = user.writePassword();
          if(isPass){
            cout << "Starting operation...\n";
          }
          else {
            cout << "Wrong password exiting!";
            break;
          }
        }
        else {
            bool isPassedRoot = root.isRootPassedTest();
            if (isPassedRoot) {
                bool isPass = root.writeRootPassword();
                if (isPass) {
                    cout << "Starting operation...\n";
                }
                else {
                    cout << "Wrong password exiting!";
                    break;
                }
            }
        }
        if (console == "exit") {
            cout << "Exiting...\n";
            break;
        } else if (console == "echo") {
            string echo;
            cout << "Write what you need to output: ";
            cin >> echo;
            cout << echo << endl;
        } else if (console == "create-user") {
            if(canRoot){
              user.create_user();
            }
            else {
              cout << "Only super user can do this operation!\n\n";
            }
        } else if (console == "help"){
          for(int i = 0; i < 3 ; ++i){
            for(int j = 0; j < 2 ; ++j){
              cout << help[i][j] << "\t" << endl;
            }
          }
        } else if (console == "passwd"){
          if(canRoot){
            root.create_root_pass();
          }
          else {
            cout << "Only super user can do this operation!\n\n";
          }
        } else if (console == "set-language"){
          language.setLanguage();
        } else if (console == "select-sudo") {
            if (userSel == true) {
                userSel = false;
                root.selectSuperUser();
            }
            else {
                cout << "Root is already selected!\n\n";
            }
        }
    }
}
