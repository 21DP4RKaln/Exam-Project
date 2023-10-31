#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <map>

using namespace std;

// Struktūra Group satur informāciju par grupām, tajā skaitā grupas nosaukumu, profesiju un klasi, kā arī pasniedzēju un grupu sarakstus un pasakumu sarakstu
struct Group {
    string name;
    string profession;
    string groupClass;
    string event;
    int groupSize;
    vector<string> teachers;
    vector<string> groups;
    vector<string> events;
};

// Struktūra Teacher satur informāciju par pasniedzējiem, tostarp vārdu, uzvārdu, kodu, mācību priekšmetu un grupu sarakstus
struct Teacher {
    string name;
    string surname;
    string Tcode;
    string subject;
    vector<string> groups;
};

// Struktūra Student satur informāciju par studentiem, tostarp vārdu, uzvārdu, grupas nosaukumu un studenta kodu
struct Student {
    string name;
    string surname;
    string group;
    string code;
};

// Struktūra "Event" satur informāciju par pasakumiem, tostarp nosaukumu, aprakstu, cenu un grupu sarakstu, kuras piedalās tajā
struct Event {
    string name;
    string description;
    float cost;
    int groupSize;
    vector<string> group;
    map<string, Event> events;
};

// Šī ir funkcija, kas saucas printSummary, un tās mērķis ir izvadīt informāciju cik ir izveidotas grupas, skolotāji, studenti un notikumi
void printSummary(const vector<Group>& groups, const vector<Teacher>& teachers, const vector<Student>& students, const vector<Event>& events) {
    cout << "\n\033[1;36mSumary\033[0m" << endl;
    cout << "\033[1m------------------------------------------\033\[0m\n" << endl;
    cout << "\033[1m- Groups: \033[0m" << groups.size() << endl;
    cout << "\033[1m- Teachers: \033[0m" << teachers.size() << endl;
    cout << "\033[1m- Students: \033[0m" << students.size() << endl;
    cout << "\033[1m- Events: \033[0m" << events.size() << endl;
    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
}

int main() {

    // Atvēras faila straumus dažāda tipa failiem
    ofstream groupFile, teacherFile, studentFile, eventFile;

    groupFile.open("groups.txt");
    teacherFile.open("teachers.txt");
    studentFile.open("students.txt");
    eventFile.open("events.txt");

    // Inicializējas vektors dažāda tipa datiem
    vector<Group> groups;
    vector<Teacher> teachers;
    vector<Student> students;
    vector<Event> events;

    char choice;
    // Izmantojās do-while cikls, lai nepārtraukti parādītu izvēlni, tik līdz lietotājs izvēlas
    do {
        // Parādas galvena izvēlne
        cout << "\n\t\033[1;4mWelcome to the School Administration System\033[0m" << endl;
        cout << "\n\033[1m------------------------------------------" << endl;
        cout << "1. Groups" << endl;
        cout << "2. Teachers" << endl;
        cout << "3. Students" << endl;
        cout << "4. Events" << endl;
        cout << "5. Summary" << endl;
        cout << "6. Exit" << endl;
        cout << "------------------------------------------\033[0m" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Izmantojas switch izteiksme, lai noteiktu, kuru darbību veikt, pamatojoties uz lietotāja izvēli
        switch (choice)  {
        char Gchoice, Tchoice, Schoice, Echoice;
        case '1': //  Ja lietotājs izvēlās "Grupas"
            system("clear"); {
            // Izmantojas cita switch izteiksme, lai noteiktu, kuru darbību veikt, pamatojoties uz lietotāja izvēles iekšā "Grupas" apakšizvēlne
            cout << "\n\t\033[1mThe School Administration System\033[0m\n" << endl;
            cout << "\033[1;36mGroups\033[0m" << endl;
            cout << "\033[1m------------------------------------------" << endl;
            cout << "1. Create new group" << endl;
            cout << "2. Delete group" << endl;
            cout << "3. List students in a group" << endl;
            cout << "4. List of group" << endl;
            cout << "5. Search group" << endl;
            cout << "6. Return to main menu" << endl;
            cout << "------------------------------------------\033[0m" << endl;
            cout << "Enter your choice: ";
            cin >> Gchoice;

            switch (Gchoice) {
            case '1': // Izvēle, lietotājam ir iespēja to izveidot
                system("clear"); {
                Group g;
                  
                cout << "\n\033[1;34mAdding group\033[0m" << endl;
                cout << "\033[1m------------------------------------------" << endl;
                cout << "\nEnter the name of the group: ";
                cin >> g.name; //Ierakstās grupas nosaukums
  
                cout << "Enter the profession of the group: "; //Šeit lietotājs ievada grupas profesiju
                cin.ignore(); 
                getline(cin, g.profession);

                //Ja lauks ir tukš, tad lietotājam vajadzēs rakstīt velreiz
                if (g.profession.empty()) {
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Profession cannot be empty.\033[0m" << endl;
                    cout << "\033[31mYou need retry.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                        cin.ignore();
                        cin.get();
                  
                    system("clear");
                    break;
                }
                //Parbaude ja jau eksistē grupa ar tādu nosaukumu, kuru ievaddija lietotājs
                bool groupExists = false;
                for (auto& existingGroup : groups) {
                    if (existingGroup.name == g.name) {
                        groupExists = true;
                        break;
                    }
                }  
                
                if (groupExists) { //Ja grupa ar tādu nosaukumu jau eksistē, tad izvadīsies kļūda
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Group with the name \"" << g.name << "\" already exists.\033[0m" << endl;
                    cout << "\033[31mYou need retry, and create not existing group.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                          cin.ignore();
                          cin.get();
                  
                    system("clear");
                    break;
                }
                else { //Ja nē, tad grupa un tās profesija ierakstīsies .txt faila
                    groups.push_back(g);
                    groupFile << g.name << " " << g.profession << " " << g.groupClass << endl;
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[32mGroup \"" << g.name << "\" added successfully..\033[0m" << endl;
                  
                    this_thread::sleep_for(chrono::seconds(2));
                    system("clear");
                }

              break;
            }
              
            case '2': // Izvēle, lietotājas var izdzēst grupu kura jau eksistē faila 
                system("clear"); {
                string groupName;

                // Lai izdzēstu grupu vajag ievadīt grupas nosaukumu, kuru vēlaties izdzēst  
                cout << "\033[1;34mDeleting group\033[0m" << endl;
                cout << "\033[1m------------------------------------------" << endl;
                cout << "\nEnter the name of the group to delete: ";
                cin >> groupName;

                // Meklējas grupa pēc tās nosaukuma  
                auto it = find_if(groups.begin(), groups.end(), [&](Group g) { return g.name == groupName; });


                if (it != groups.end()) { // Ja grupa ir atrasta, tad tā tiek izdzēsta no saraksta un atjauno failu "groups.txt" 
                    groups.erase(it);
                    groupFile.close();
                    groupFile.open("groups.txt", ios::out | ios::trunc);
                    for (auto g : groups) {
                        groupFile << g.name << " " << g.profession << endl;
                    }
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[32mGroup deleted successfully!.\033[0m\n" << endl;
        
                    this_thread::sleep_for(chrono::seconds(2)); // Šī ir funkcija sleep, kura pēc divam sekundem notīra konsoli   
                    system("clear");
                }
                
                else { // Ja grupa nav atrasta, tad izvadas kļūda, kura paziņo par kļūdu un lūdz mēģināt vēlreiz ar grupu kura ir ierakstīta faila  
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Group not found.\033[0m" << endl;
                    cout << "\033[31mYou need retry, with existing group\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                          cin.ignore();
                          cin.get();
                  
                    system("clear");
                }
              break;
            }
              
            case '3': // Izvēle, lietotājs var izvēleties grupu kura paskatīties sarakstu ar studentiem 
              system("clear"); {
              string groupName;
              char goBackChoice;

              // Ierakstās grupas nosaukums, no kuras jūs gribāt redzēt studentu sarakstu
              cout << "\033[1;34mList students in group\033[0m" << endl;
              cout << "\033[1m------------------------------------------" << endl;
              cout << "\nEnter the name of the group: ";

              cin >> groupName;

              auto it = find_if(groups.begin(), groups.end(), [&](Group g) { return g.name == groupName; });

              if (it != groups.end()) {
              string fileName = groupName + ".txt";
              ifstream groupFile(fileName);

                // Atvērto failu pārbauda un ielasa datus no tā
                if (groupFile.is_open()) {
                string line;
                vector<tuple<string, string, string>> students;
                while (getline(groupFile, line)) {
                    stringstream ss(line);
                    string name, surname, code;
                    ss >> name >> surname >> code;
                    students.push_back(make_tuple( name, surname, code ));
                }
                groupFile.close();
          
                system("clear");
          
                // Sakārtošanas veida izvēle
                char sortChoice;
                cout << "\033[1;34mList students in group\033[0m" << endl;
                cout << "\033[1m------------------------------------------" << endl;
                cout << "\nChoose sorting order:";
                cout << "\n1. By name (A-Z)\n2. By surname (A-Z)\n";
                cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                cout << "Enter your choice: "; 
              
                cin >> sortChoice;

                // Sakārto studentus atbilstoši izvēlētajam veidam
                if (sortChoice == '2') {
                    sort(students.begin(), students.end(), [](tuple<string, string, string>& a, tuple<string, string, string>& b) {
                        string aLastName = get<1>(a);
                        string bLastName = get<1>(b);
                        return aLastName < bLastName;
                    });
                }
                else {
                    sort(students.begin(), students.end(), [](tuple<string, string, string>& a, tuple<string, string, string>& b) {
                      string aFirstName = get<0>(a);
                      string bFirstName = get<0>(b);
                      return aFirstName < bFirstName;
                    });
                }

                system("clear");

                // Izvada studentu sarakstu no izvēlētās grupas
                if (sortChoice == '2') { //Ja izvēlas 2, tad saraksts kārtots pēc uzvārda
                    cout << "\033[1;34mList of students in group " << groupName << " (sorted ";
                    cout << "by surname A-Z)\033[0m" << endl;
                    cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                    for (auto& student : students) {
                      cout << get<1>(student) << " " << get<0>(student) << " (personal code: " << get<2>(student) << ")" << endl;
                }
                }
                else if (sortChoice == '1') { // Ja 1, tad saraksts kārtots pēc vārda
                    cout << "\033[1;34mList of students in group " << groupName << " (sorted ";
                    cout << "by name A-Z)\033[0m" << endl;
                    cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                    for (auto& student : students) {
                      cout << get<0>(student) << " " << get<1>(student) << " (personal code: " << get<2>(student) << ")" << endl;
                  }
                } 
                else { // Ja kaut kas cits, tad kļūda
                  system("clear");
                  cout << "\n\033[1;31mError: Invalid choice. Please try again.\033[0m" << endl;
                  this_thread::sleep_for(chrono::seconds(1));
                  system("clear");
                  break;
                }

                // Izzeja uz galvenu izvelni
                cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                cout << "Press enter to return to the main menu...";
                cin.ignore();
                cin.get();

                system("clear");
            }
        }
                // Ja grupa nav atrasta, tad parāda kļūdas ziņojumu un atgriežas galvenajā izvēlnē
                else {
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Group not found.\033[0m" << endl;
                    cout << "\033[31mYou need retry, with existing group\033[0m" << endl;
                  
                     cout << "\nPress enter to return to the main menu...";
                          cin.ignore();
                          cin.get();
                  
                          system("clear");
                }
              break;
            }
              
            case '4': // Izvēle, lietotājs varēs redzēt sarakstu ar visām grupām 
                system("clear"); {
                char goBackChoice;

                // Sakartojās pēc alfabēta
                sort(groups.begin(), groups.end(), [](const Group& g1, const Group& g2) {
                    return g1.name < g2.name;
                    });

                // Izvade
                cout << "\033[1;34mList of group\033[0m" << endl;
                cout << "\033[1m------------------------------------------" << endl;
                cout << "List of all groups (sorted by name A-Z):\033[0m\n" << endl;
 
                for (auto& g : groups) {
                    cout << g.name << " (profession: " << g.profession << ") - " << g.groupSize << " students" << endl;
}
                  
                cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                cout << "Press enter to return to the previous menu...";
                        cin.ignore();
                        cin.get();

                        system("clear");
              break;
            }

            case '5': // Izvēle, lietotājs var izvēlēties kā meklēt grupu
              system("clear"); {
              char GSearchchoice;
              cout << "\033[1;36mGroup Search\033[0m" << endl;
              cout << "\033[1m------------------------------------------" << endl;
              cout << "1. Search group by name" << endl;
              cout << "2. Search group by profession" << endl;
              cout << "3. Search group by number of students" << endl;
              cout << "4. Return to main menu" << endl;
              cout << "------------------------------------------\033[0m" << endl;
              cout << "Enter your choice: ";
              cin >> GSearchchoice;

              switch (GSearchchoice) {
              if (groups.empty()) {
                    system("clear");
                    cout << "\n\033[1;31mError: No groups have been added yet, add first.\033[0m\n";
                    cout << "\nPress enter to return to the main menu...";
                      
                      cin.ignore();
                      cin.get();
                      
                      system("clear");
                      break;
                    }
                
              case '1': // Meklēt pēc vārda
                system("clear"); {
                  string groupName;
                  
                  cout << "\n\033[1;34mSearch group by name\033[0m" << endl;
                  cout << "\033[1m------------------------------------------" << endl;
                  cout << "\nEnter the name of the group: ";
                  cin >> groupName;

                      // Parbaude ja ir tāda grupa
                      bool groupFound = false;
                      for (auto& g : groups) {
                        if (g.name == groupName) { // Ja ir, izvade
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "\033[32mGroup found\033[0m" << endl;
                          this_thread::sleep_for(chrono::seconds(5));
                          system("clear");
                          
                          cout << setw(5) << "\033[1;34mGroups" << " " << "|" << " " << setw(10) << "Professions" << " " << "|" << " " << setw(10) << "Number of students\033[0m" << endl;
                          cout << " " << endl; 
                          cout << setw(5) << g.name << setw(10) << g.profession << setw(14) << g.groupSize << endl;
                          groupFound = true;
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "Press enter to return to the group search menu...";
                    
                          cin.ignore();
                          cin.get();
                          system("clear");
                        break;
                        }
                      }

                    if (!groupFound) { // Ja nav, tad kļūda
                      cout << "\033[1m------------------------------------------\033[0m" << endl;
                      cout << "\033[31mError: Group not found.\033[0m" << endl;
                      cout << "\033[31mYou need retry, with existing group\033[0m" << endl;
                      cout << "\nPress enter to return to the group search menu...";
                    
                          cin.ignore();
                          cin.get();
                          system("clear");
                    }
              break;
              }
                  
              case '2': // Meklē pēc profesijām         
                system("clear"); {
                  string groupProf;
                  
                  cout << "\n\033[1;34mSearch group by profession\033[0m" << endl;
                  cout << "\033[1m------------------------------------------" << endl;
                  cout << "\nEnter group profession: ";
                  cin >> groupProf;

                      //Parbaude ja ir tāda profesija
                      bool groupFound = false;
                      for (auto& g : groups) {
                        if (g.profession == groupProf) { //Izvade
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "\033[32mGroup with this profession found\033[0m" << endl;
                          this_thread::sleep_for(chrono::seconds(5));
                          system("clear");
                          
                          cout << setw(5) << "\033[1;34mGroups" << " " << "|" << " " << setw(10) << "Professions" << " " << "|" << " " << setw(10) << "Number of students\033[0m" << endl;
                          cout << " " << endl; 
                          cout << setw(5) << g.name << setw(10) << g.profession << setw(14) << g.groupSize << endl;
                          groupFound = true;
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "Press enter to return to the group search menu...";
                    
                          cin.ignore();
                          cin.get();
                          system("clear");
                        break;
                        }
                      }

                      if (!groupFound) { //Kļūda
                        cout << "\033[1m------------------------------------------\033[0m" << endl;
                        cout << "\033[31mError: Group with that profession not found.\033[0m" << endl;
                        cout << "\033[31mYou need retry, with added profession.\033[0m" << endl;
                        cout << "\nPress enter to return to the group search menu...";
                      
                            cin.ignore();
                            cin.get();
                            system("clear");
                      }
                  break;
                }
            
              case '3': // Meklē pēc studentu skaitu
                system("clear"); {
                  int numStudents;
                  
                  cout << "\n\033[1;34mSearch group by number of students\033[0m" << endl;
                  cout << "\033[1m------------------------------------------" << endl;
                  cout << "\nEnter the number of students: ";
                  cin >> numStudents;

                  //Parbaude ja ir grupa ar tādu studentu skaitu
                  bool groupFound = false;
                  for (auto& g : groups) {
                    if (g.groupSize == numStudents) { //Izvade
                      cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                      cout << "\033[32mGroup found with this student number\033[0m" << endl;
                      this_thread::sleep_for(chrono::seconds(5));
                      system("clear");
                          
                      cout << setw(5) << "\033[1;34mGroups" << " " << "|" << " " << setw(10) << "Professions" << " " << "|" << " " << setw(10) << "Number of students\033[0m" << endl;
                      cout << " " << endl; 
                      cout << setw(5) << g.name << setw(10) << g.profession << setw(14) << g.groupSize << endl;
                      groupFound = true;
                      cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                      cout << "Press enter to return to the group search menu...";
                    
                          cin.ignore();
                          cin.get();
                          system("clear");
                      break;
                    }
                  }

                      if (!groupFound) { //Kļūda
                        cout << "\033[1m------------------------------------------\033[0m" << endl;
                        cout << "\033[31mError: Group not found.\033[0m" << endl;
                        cout << "\033[31mYou need retry, with group where is students or with right number.\033[0m" << endl;
                        cout << "\nPress enter to return to the group search menu...";

                        cin.ignore();
                        cin.get();
                        system("clear");
                    }
                  break;
                }
                  
              case '4': //Iziet uz galveno izvēlni
                system("clear"); {
                  GSearchchoice = '0';
                  
                break;
                default: {
                    system("clear");
                    cout << "\n\033[1;31mError: Invalid choice. Please try again.\033[0m" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    system("clear");
                  }
                }
              }
              break;
            }
              
            case '6': // Izvēle, lietotājs atgriežās galvenāja izvēlne
                system("clear"); {
                Gchoice = '0';
                  
              break;
            default: { // Izvadas kļūda, ja lietotājs ievada, nevajadzīgo simbolu/cipacu
            system("clear");
            cout << "\n\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("clear");
            }
                }
            }
          break;
        }
          
        case '2': // Ja lietotājs izvēlās "Skolotājs"
            system("clear"); { 
            // Izmantojas cita switch izteiksme, lai noteiktu, kuru darbību veikt, pamatojoties uz lietotāja izvēles iekšā "Skolotāji" apakšizvēlne
            cout << "\n\t\033[1mThe School Administration System\033[0m\n" << endl;
            cout << "\033[1;36mTeachers\033[0m" << endl;
            cout << "\033[1m------------------------------------------" << endl;
            cout << "1. Create new teacher" << endl;
            cout << "2. Add an teacher to group" << endl;
            cout << "3. Remove an teacher from group" << endl;
            cout << "4. List of all teachers" << endl;
            cout << "5. Return to main menu" << endl;
            cout << "------------------------------------------\033[0m" << endl;
            cout << "Enter your choice: ";
            cin >> Tchoice;

            switch (Tchoice) {
                    case '1': // Izvēle, kur var pievienot skolotāju
                        system("clear"); { 
                          cout << "\n\033[1;34mAdding teacher\033[0m" << endl;
                          cout << "\033[1m------------------------------------------\n" << endl;

                          string firstName, lastName, Tcode, subject;

                          // Datu ievade
                          cout << "Enter the first name: ";
                          cin >> firstName;

                          cout << "Enter the last name: ";
                          cin >> lastName;

                          cout << "Enter the personal code: ";
                          cin >> Tcode;

                          // Parbaudē ja eksistē skolotājs ar tādu personālo kodu 
                          bool exists = false;
                          for (const auto& teacher : teachers) {
                              if (teacher.Tcode == Tcode) {
                                  exists = true;
                                  break;
                                }
                            }
                          
                          // Ja ir, tad kļūda 
                          if (exists) {
                              cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                              cout << "\033[31mError: a teacher with this personal code already exists.\033[0m" << endl;
                              cout << "\033[31mYou need retry, and add teacher with unwritten personal code.\033[0m" << endl;
                              cout << "\nPress enter to return to the main menu...";
                                  cin.ignore();
                                  cin.get();
                              
                                system("clear");
                            }
                          else { // Ja nav tad var tālak ievadīt skolotāja datus
                              cout << "Enter the subject the teacher teaches: ";
                              cin >> subject;

                              // Dati ievadās .txt faila
                              Teacher newTeacher;
                              newTeacher.name = firstName;
                              newTeacher.surname = lastName;
                              newTeacher.Tcode = Tcode;
                              newTeacher.subject = subject;
                              newTeacher.groups = {};

                              teachers.push_back(newTeacher);
                                
                            teacherFile << newTeacher.name << " " << newTeacher.surname << " " << newTeacher.Tcode << " " << newTeacher.subject << " " << endl;
                            
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "\033[32mTeacher" << " " << newTeacher.name << " " << "added successfully.\033[0m" << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            system("clear");
                            }

                        break;
                      }

                    case '2': // Izvēle, kur var pievienot izveidotot skolotāju grupai
                        system("clear"); {
                          cout << "\033[1;34mAdding existing teachers to group\033[0m" << endl;
                          cout << "\033[1m------------------------------------------\n" << endl;

                          string code, groupName;

                          // Vajadzīga sklotāja, meklēšana
                          cout << "Enter the personal code of the teacher: ";
                          cin >> code;

                          // Parbaude vai tas skolotājs ir izveidots
                          bool found = false;
                          bool Gfound = false;
                          for (auto& teacher : teachers) {
                              if (teacher.Tcode == code) { // Ja nē, tad var pievienot grupai
                                  found = true;
                                  cout << "Enter the name of the group: ";
                                  cin >> groupName;
                                  for (auto &group : groups) { // Parbaude vai grupa ir izveidota
                                    if (group.name == groupName) { // Jā, tad skolotājs pievienojas
                                      Gfound = true;
                                      teacher.groups.push_back(groupName);
                                      cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                                      cout << "\033[32mThe teacher has been added to the group successfully.\033[0m\n" << endl;
                                          this_thread::sleep_for(chrono::seconds(1));
                                          system("clear");
                                          break;
                                    }
                                  }

                                  if (!Gfound) { // Nē, izvadās kļūda
                                  cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                                  cout << "\033[31mError: group with this name not found.\033[0m" << endl;
                                  cout << "\033[31mYou need retry, and add teacher with existing group.\033[0m" << endl;
                                  
                                  cout << "\nPress enter to return to the main menu...";
                              
                                  cin.ignore();
                                  cin.get();
                                  system("clear");
                                  break;
                                }
                              }
                          }

                          if (!found) { // Ja jā, tad skolotājs nevarēs 
                              cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                              cout << "\033[31mError: no teacher with this personal code not found.\033[0m" << endl;
                              cout << "\033[31mYou need retry, and add teacher with existing personal code.\033[0m" << endl;
                              cout << "\nPress enter to return to the main menu...";
                              
                                  cin.ignore();
                                  cin.get();
                              
                                system("clear");
                          }
                          break;
                      }

                    case '3': // Izvēle, kur var noņemt skolotāju no grupas
                        system("clear"); { 
                          cout << "\033[1;34mRemoving teacher from group\033[0m" << endl;
                          cout << "\033[1m------------------------------------------\n" << endl;

                          string code, groupName;

                          cout << "\nEnter the personal code of the teacher: ";
                          cin >> code;

                          // Pārbaude ja ir tas skolotājs
                          bool found = false;
                          for (auto& teacher : teachers) {
                              if (teacher.Tcode == code) {
                                  found = true;
                                  // Pārbaude ja ir tāda grupa
                                  bool validGroup = false;
                                  while (!validGroup) {
                                    
                                      cout << "Name of group whose from teacher you removing: ";
                                      cin >> groupName;

                                      //Dzēš no skolotāja .txt faila grupas nosaukumu
                                      auto it = find(teacher.groups.begin(),
                                          teacher.groups.end(), groupName);
                                    
                                      if (it != teacher.groups.end()) {
                                          teacher.groups.erase(it);

                                          cout << "\n\033[1m------------------------------------------" << endl;
                                          cout << "\033[32mThe teacher has been removed from the group successfully.\033[0m\n" << endl;
                                          validGroup = true;
                                        
                                          this_thread::sleep_for(chrono::seconds(1));
                                          system("clear");
                                        }
                                        else { //Kļūda

                                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                                          cout << "\033[31mError: the teacher is not a member of this group.\033[0m" << endl;
                                          cout << "\033[31mYou need retry, and remove teacher who are in this group.\033[0m" << endl;
                                          cout << "\nPress enter to return to the main menu...";
                              
                                          cin.ignore();
                                          cin.get();

                                          system("clear");
                                          break;
                                        }
                                  }

                                break;
                              }
                            }

                            if (!found) { // Kļūda 
                                cout << "\n\033[1m------------------------------------------" << endl;
                                cout << "\033[31mError: no teacher with this personal code found.\033[0m" << endl;
                                cout << "\033[31mYou need retry, and add teacher with existing personal code.\033[0m" << endl;
                                cout << "\nPress enter to return to the main menu...";
                              
                                    cin.ignore();
                                    cin.get();
                              
                                system("clear");
                          }
                        break;
                      }
                      
                    case '4': // Izvēle, kur var paskatīties sarakstu ar visiem skolotājiem
                      system("clear"); {
                          cout << "\033[1;34mList of teachers \033[0m" << endl;
                          cout << "\033[1m------------------------------------------\033[0m" << endl;

                        // Skolotāja datu izvade
                        for (const auto& teacher : teachers) {
                          cout << "\033[1mName: \033[0m" << teacher.name << " " << teacher.surname << endl;
                          cout << "\033[1mPersonal Code: \033[0m" << teacher.Tcode << endl;
                          cout << "\033[1mSubject: \033[0m" << teacher.subject << endl;
                          cout << "\033[1mGroups: \033[0m";
                          for (const auto& group : teacher.groups) {
                            cout << group << ";" << " ";
                          }
                          cout << endl;
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                        }
                        
                        cout << "Press enter to return to the previous menu...";
                        cin.ignore();
                        cin.get();

                        system("clear");
                        break;
                        }

                    case '5': // Izvēle, kura atgriež uz galveno izvēlni
                      system("clear"); {
                Tchoice = '0';
                  
              break;
            default: {
            system("clear");
            cout << "\n\033[1;31mInvalid choice. Please try again.\033[0m" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("clear");
            }
                }
            }
          break;
        }
                
        case '3': // Ja lietotājs izvēlās "Studenti"
            system("clear"); {
            // Izmantojas cita switch izteiksme, lai noteiktu, kuru darbību veikt, pamatojoties uz lietotāja izvēles iekšā "Studenti" apakšizvēlne
            cout << "\n\t\033[1mThe School Administration System\033[0m\n" << endl;
            cout << "\n\033[1;36mStudents\033[0m" << endl;
            cout << "\033[1m------------------------------------------" << endl;
            cout << "1. Add a student to a group" << endl;
            cout << "2. Remove a student from a group" << endl;
            cout << "3. List all students" << endl;
            cout << "4. Return to main menu" << endl;
            cout << "------------------------------------------\033[0m" << endl;
            cout << "Enter your choice: ";
            cin >> Schoice;

            switch (Schoice) {
            case '1': // Izvēle var pievienot studentu
                system("clear"); {
                Student s;

                // Datu ierakstīšana
                cout << "\n\033[1;34mAdding student\033[0m" << endl;
                cout << "\033[1m------------------------------------------" << endl;
                cout << "\nEnter the name of the student: ";
                cin >> s.name;
                cout << "Enter the surname of the student: ";
                cin >> s.surname;

                bool codeExists = true;
                while (codeExists) {
                    cout << "Enter the personal code for the student: ";
                    cin >> s.code;
                    codeExists = false;

                    // Parbaude ja students ar tādu kodu eksistē
                    for (auto const& student : students) {
                        if (student.code == s.code) { //Ja eskistē, tad kļūda
                            codeExists = true;
                            cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                            cout << "\033[31mError: Code already exists.\033[0m" << endl;
                            cout << "\033[31mYou need retry, and add not existing personal code.\033[0m" << endl;
                            cout << "\nPress enter to return to the main menu...";
                              
                                cin.ignore();
                                cin.get();
                          
                            system("clear");
                            break;
                        }
                    }
                }

                // Pievienošana grupa
                cout << "Enter the name of the group to which the student belongs: ";
                cin >> s.group;

                // Parbaude uz ievadītas grupas eksistēšanu  
                bool groupExists = false;
                for (auto const& group : groups) {
                    if (group.name == s.group) {
                        groupExists = true;
                        break;
                    }
                }

                if (!groupExists) { // Ja nē, tad kļūda
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Group does not exist. Please create the group first.\033[0m" << endl;
                    cout << "\033[31mYou need retry, create group where you wanna add, or write right name of group.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                              
                        cin.ignore();
                        cin.get();
                  
                    system("clear");
                    break;
                }

                // Parbaude uz to ja tas students jau ir tajā grupā
                bool studentExists = false;
                for (auto const& student : students) {
                    if (student.code == s.code && student.group == s.group) {
                        studentExists = true;
                        cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                        cout << "\033[31mError: Student already exists in the group.\033[0m" << endl;
                        cout << "\033[31mYou need retry.\033[0m" << endl;
                        cout << "\nPress enter to return to the main menu...";
                              
                        cin.ignore();
                        cin.get();

                        system("clear");
                        break;
                    }
                }

                if (!studentExists) {  // Ja nē, tad studenta dati ierakstās faila
                    students.push_back(s);
                    studentFile << s.name << " " << s.surname << " "<< "(Personal code" << s.code << ")" <<" " << s.group << endl;
                    string fileName = s.group + ".txt";
                    ofstream groupFile;
                    groupFile.open(fileName, ios::app);
                    groupFile << s.name << " " << s.surname << " " << s.code << endl;
                    groupFile.close();
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[32mStudent added to group successfully.\033[0m\n" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    system("clear");
                }
                break;
            }
              
            case '2': // Izvēle var noņemt studentu
                system("clear"); {
                string groupName, code;

                //Datu ierakstīšana
                cout << "\n\033[1;34mRemoving student\033[0m" << endl;
                cout << "\033[1m------------------------------------------" << endl;
                cout << "\nEnter the name of the group from which the student should be removed: ";
                cin >> groupName;
                cout << "Enter the personal code of the student to be removed: \033[0m";
                cin >> code;

                // Ievaditās grupas parbaude
                bool groupExists = false, studentExists = false;
                int studentIndex = -1;
                for (int i = 0; i < groups.size(); i++) {
                    if (groups[i].name == groupName) {
                        groupExists = true;
                        break;
                    }
                }

                if (!groupExists) { //Kļūda ja neeksistē grupa
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Group does not exist.\033[0m" << endl;
                    cout << "\033[31mYou need retry, first create group, or write right group name.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                              
                        cin.ignore();
                        cin.get();

                    system("clear");
                    break;
                }

                // Ievadīta studenta personāla koda pārbaude
                for (int i = 0; i < students.size(); i++) {
                    if (students[i].code == code && students[i].group == groupName) {
                        studentExists = true;
                        studentIndex = i;
                        break;
                    }
                }

                if (!studentExists) { // Kļūda ja ne eksistē
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Student does not exist in the group.\033[0m" << endl;
                    cout << "\033[31mYou need retry.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                              
                        cin.ignore();
                        cin.get();
                  
                    system("clear");
                    break;
                }

                // Dzēšās studenta dati no .txt faila
                students.erase(students.begin() + studentIndex);
                cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                cout << "\033[32mStudent removed from group successfully.\033[0m" << endl;
                  
                this_thread::sleep_for(chrono::seconds(1));
                system("clear");
                break;
            }

            case '3': // Izvēle ir studentu saraksts
              system("clear"); {
                  if (students.empty()) { // Kļūda ja nav ievadīti studenti
                    system("clear");
                    cout << "\n\033[1;31mError: No students have been added yet, add first.\033[0m\n";
                    cout << "\nPress enter to return to the main menu...";
                      
                      cin.ignore();
                      cin.get();
                      
                      system("clear");
                      break;
                    }

                    // Izvēle kā kartot studentus, (pēc vārda, pēc uzvārda, pēc grupas)
                    cout << "\n\033[1;34mList of Students\033[0m" << endl;
                    cout << "\033[1m------------------------------------------\033[0m" << endl;

                    char sort_choice;
                    cout << "\n\033[1mChoose sorting order: \033[0m";
                    cout << "\n\033[1m1. By name\n2. By surname\n3. By group\n\033[0m";
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "Enter your choice: ";
                    cin >> sort_choice;
                    system("clear");

                    //Veidojās vectora kopija
                    vector<Student> students_copy = students;

                    // Lietotājs izvēlas kā kārtot
                    switch (sort_choice) {
                        case '1': // Kārto pēc vārda
                            system("clear"); { 
                            
                            // Izvade
                            cout << "\n\033[1;34mList of students (sorted by name A-Z)\033[0m\n";
                            cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                            sort(students_copy.begin(), students_copy.end(), [](const Student& s1, const Student& s2) { return s1.name < s2.name; });
                            // izvadās vārdi, uzvārdi un grupas
                            for (const auto& student : students_copy) {
                              cout << student.name << " " << student.surname << " " << "(In group:" << " " << student.group << ")" << endl;
                            }
                            cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                            cout << "Press enter to return to the main menu...";
                              cin.ignore();
                              cin.get();
                              system("clear");
                          break;
                        }
                      
                        case '2': // Kārto pēc uzvārda
                          system("clear"); {

                            // Izvade
                            cout << "\n\033[1;34mList of students (sorted by surname A-Z)\033[0m\n";
                            cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                            sort(students_copy.begin(), students_copy.end(), [](const Student& s1, const Student& s2) { return s1.surname < s2.surname; }); 
                            // izvadās uzvārdi, vārdi un grupas
                            for (const auto& student : students_copy) {
                              cout << student.surname << " " << student.name << " " << "(In group:" << " " << student.group << ")" << endl;
                            }
                            cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                            cout << "Press enter to return to the main menu...";
                              cin.ignore();
                              cin.get();
                              system("clear");
                          break;
                        }
                      
                        case '3': //Kārto pēc grupas
                          system("clear"); { 

                            //Izvade
                            cout << "\n\033[1;34mList of students (sorted by group name A-Z)\033[0m\n";
                            cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                            sort(students_copy.begin(), students_copy.end(), [](const Student& s1, const Student& s2) { return s1.group < s2.group; });
                            // izvadās grupas, vārdi un uzvārdi 
                            for (const auto& student : students_copy) {
                              cout << student.group << " " << student.name << " " << student.surname  <<  endl;
                            }
                            cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                            cout << "Press enter to return to the main menu...";
                              cin.ignore();
                              cin.get();
                              system("clear");
                          break;
                        }
                        default: // Kļūda
                            cout << "\n\033[1;31mError: Invalid choice. Returning to main menu...\033[0m\n" << endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            system("clear");
                            break;
                        }
                    }
              
            case '4': // Izvēle, kura atgriež uz galveno izvēlni 
                system("clear"); {
                Schoice = '0';
                  
              break;
            default: {
            system("clear");
            cout << "\n\033[1;31mError: Invalid choice. Please try again.\033[0m" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("clear");
            }
                }
            }
          break;
        }

        case '4': // Ja lietotājs izvēlās "Pasākumi"
            system("clear"); {
            // Izmantojas cita switch izteiksme, lai noteiktu, kuru darbību veikt, pamatojoties uz lietotāja izvēles iekšā "Pasākumi" apakšizvēlne
            cout << "\n\t\033[1mThe School Administration System\033[0m\n" << endl;
            cout << "\033[1;36mEvents\033[0m" << endl;
            cout << "\033[1m------------------------------------------" << endl;
            cout << "1. Create event" << endl;
            cout << "2. Delete event" << endl;
            cout << "3. Add group in event" << endl;
            cout << "4. Remove group from event" << endl; 
            cout << "5. Search events" << endl;
            cout << "6. List of events" << endl;
            cout << "7. Return to main menu" << endl;
            cout << "------------------------------------------\033[0m" << endl;
            cout << "Enter your choice: ";
            cin >> Echoice;

            switch (Echoice) {
            case '1': // Izvēle, var izveidot pasākumu
                system("clear"); {
                Event e;

                //Datu ievadīšana
                cout << "\033[1;34mCreating events\033[0m" << endl;
                cout << "\033[1m------------------------------------------" << endl;
                cout << "\n\033[1mEnter the name of Event: \033[0m";
                cin >> e.name;
                cout << "\033[1mEnter the descripton of Event: \033[0m";
                cin.ignore();
                getline(cin, e.description);
                if (e.description.empty()) { // Parbaude lai apraksts nav tukšs
                    cout << "\n\033[1m------------------------------------------" << endl;
                    cout << "\033[31mError: Description cannot be empty.\033[0m" << endl;
                    cout << "\033[31mYou need retry.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                              
                        cin.ignore();
                        cin.get();
                  
                    system("clear");
                    break;
                }
                cout << "\033[1mEnter how much cost of Event: \033[0m";
                cin >> e.cost;

                // Parbaude ja jau eksistē pasākums ar tā nosaukumu
                bool eventExists = false;
                for (auto& existingEvent : events) {
                    if (existingEvent.name == e.name) {
                        eventExists = true;
                        break;
                    }
                }

                if (eventExists) { // Kļūda, ja eksistē
                    cout << "\n\033[1m------------------------------------------" << endl;
                    cout << "\033[31mError: Event with the name \"" << e.name << "\" already exists.\033[0m" << endl;
                    cout << "\033[31mYou need retry, and create event with not writted name.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                              
                        cin.ignore();
                        cin.get();
                }
                else { // Pievieno pasākumu datus .txt faila
                    events.push_back(e);
                    eventFile << e.name << " " << e.description << " " << e.cost << " " << endl;
                    cout << "\n\033[1m------------------------------------------" << endl;
                    cout << "\033[1;32mEvent \"" << e.name << "\" added successfully.\033[0m" << endl;
                    cout << "\033[1;32mDescription of Event added successfully.\033[0m\"" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    system("clear");
                }

                break;
            }
              
            case '2': // Izvēle, var idzēst pasākumu
                system("clear"); {
                string eventName;

                // Datu ievadīšana
                cout << "\033[34mDeleting events\033[0m" << endl;
                cout << "\033[1m------------------------------------------\033[0m" << endl;
                cout << "\n\033[1mEnter the name of the event to delete: \033[0m";
                cin >> eventName;

                // Parbaude ja tāds pasākums
                auto it = find_if(events.begin(), events.end(), [&](Event e) { return e.name == eventName; });
                if (it != events.end()) { // Ja ir ievadīts, tad dzēšās dati
                    events.erase(it);
                    eventFile.close();
                    eventFile.open("events.txt", ios::out | ios::trunc);
                    for (auto e : events) {
                        eventFile << e.name << " " << e.description << endl;
                    }
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[32mEvent and description deleted successfully!\033[0m" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    system("clear");
                }

                else { // Ja nē, tad kļūda
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[31mError: Event and description not found.\033[0m" << endl;
                    cout << "\033[31mYou need retry.\033[0m" << endl;
                    cout << "\nPress enter to return to the main menu...";
                              
                        cin.ignore();
                        cin.get();
                  
                    system("clear");
                }
                break;
            }
              
            case '3': // Izvēle, var pievienot grupu pasākuma
                system("clear"); {
                cout << "\n\033[34mAdd a group to event\033[0m" << endl;
                cout << "\033[1m------------------------------------------\033[0m" << endl;
                  
                string groupName, eventName;

                // Datu ievadīšana
                cout << "\033[1mEnter the group name: \033[0m";
                cin >> groupName;
                cout << "\033[1mEnter the event name: \033[0m";
                cin >> eventName;

                //Datu parbaude
                bool isGroupFound = false, isEventFound = false;
                  for (auto &group : groups) {
                    if (group.name == groupName) { 
                    
                      isGroupFound = true;
                      for (auto &event : events) {
                      
                        if (event.name == eventName) {
                          isEventFound = true;

                          // Pievieno grupas nosaukumu pasākuma grupu vektoram
                          event.group.push_back(groupName);
                          group.events.push_back(eventName);
                          // Ieraksta pasākuma datus .txt failā.
                          eventFile << eventName << " " << event.description << " " << event.cost << " ";
                        
                          for (auto &groupName : event.group) {
                              eventFile << groupName << ",";
                          }  
                          eventFile << endl;
                          
                          // Ieraksta grupas datus .txt failā
                          groupFile << group.name << " " << group.profession << " " << group.groupClass << " ";
                        
                          for (auto &teacher : group.teachers) {
                              groupFile << teacher << ",";
                          }
                          groupFile << " ";
                        
                          for (auto &student : students) {
                              // Ja students ir grupā, pievieno viņa kodu grupas informācijai
                              if (student.group == groupName) {
                                  // Pievieno grupas pasākuma nosaukumu grupas informācijai
                                  groupFile << student.code << ",";
                              }
                          }
                          groupFile << " ";
                          for (auto &eventName : group.events) {
                              groupFile << eventName << ",";
                          }
                          groupFile << endl; 
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "\033[32mGroup \"" << groupName << "\" added to event \"" << eventName << "\" successfully.\033[0m" << endl;
                          system("clear");
                          break;
                        }
                    }
                          if (!isEventFound) { // Kļūda, ja nav tāda pasākuma
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "\033[32mError: Event not found.\033[0m" << endl;
                          cout << "\nPress Enter to return to the previous menu...";
                  
                            cin.ignore();
                            cin.get();
                  
                          system("clear");
                          }
                      break;
                    }
                }    
                  if (!isGroupFound) { // Kļūda, ja nav tādas grupas
                    cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                    cout << "\033[32mError: Group not found.\033[0m" << endl;
                
                    cout << "\nPress Enter to return to the previous menu...";
                  
                      cin.ignore();
                      cin.get();

                    system("clear");  
                  break;
                }
              break;
            }
              
            case '4': // Izvēle, var noņemt grupu
                system("clear"); {
                cout << "\n\033[34mRemove a group from event\033[0m" << endl;
                cout << "\033[1m------------------------------------------\033[0m" << endl;
                  
                string groupName, eventName;

                // Datu ievade
                cout << "\033[1mEnter the group name: \033[0m";
                cin >> groupName;
                cout << "\033[1mEnter the event name: \033[0m";
                cin >> eventName;

                // Datu parbaude
                bool isGroupFound = false, isEventFound = false;
                  for (auto &group : groups) {
                    if (group.name == groupName) {
                      isGroupFound = true;
                      for (auto &event : events) {
                        if (event.name == eventName) {
                          isEventFound = true;
                            auto it = find(event.group.begin(), event.group.end(), groupName);
                            if (it != event.group.end()) {
                              event.group.erase(it);
                              auto it2 = find(group.events.begin(), group.events.end(), eventName);
                                if (it2 != group.events.end()) {
                                  group.events.erase(it2);
                                }
                                // Grupa noņemas no pasākuma
                                eventFile << eventName << " " << event.description << " " << event.cost << " ";
                                for (auto &groupName : event.group) {
                                eventFile << groupName << ",";
                                }
                              eventFile << endl;
                              cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                              cout << "\033[32mSuccessfully removed the group from the event.\033[0m" << endl;
                              system("clear");
                              break;
                            }
                        }
                      }
                      if (!isEventFound) { // Kļūda, ja nav pasākuma
                        cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                        cout << "\033[31mError: Event not found.\033[0m" << endl;
                        cout << "\033[31mYou need retry.\033[0m" << endl;
                      
                      cout << "\nPress Enter to return to the previous menu...";
                  
                          cin.ignore();
                          cin.get();
                          system("clear");
                      }
                      break;
                  }
                }
                if (!isGroupFound) { // Kļūda, ja nav grupas
                  cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                  cout << "\033[31mError: Group not found.\033[0m" << endl;
                  cout << "\033[31mYou need retry.\033[0m" << endl;
                  cout << "\nPress Enter to return to the previous menu...";
                  
                        cin.ignore();
                        cin.get();
                  
                      system("clear");
              }  
              eventFile.close();
                
              break;
            }
              
            case '5': // Izvēle, var atrast pasākumu
                system("clear"); {
                char ESearchChoice;

                // Izmantojas cita switch izteiksme, lai noteiktu, kuru darbību veikt, pamatojoties uz lietotāja izvēles apakšizvēlne
                cout << "\n\033[1;34mSearch events\033[0m" << endl;
                cout << "\033[1m------------------------------------------\n" << endl;
                cout << "1. By event name" << endl;
                cout << "2. By group name" << endl;
                cout << "3. Return to events menu" << endl;
                cout << "\n------------------------------------------\033[0m" << endl;
                cout << "Enter your choice: ";
                cin >> ESearchChoice;

                switch (ESearchChoice) {
                if (events.empty()) {
                    system("clear");
                    cout << "\n\033[1;31mError: No events have been added yet, add first.\033[0m\n";
                    cout << "\nPress enter to return to the main menu...";
                      
                      cin.ignore();
                      cin.get();
                      
                      system("clear");
                      break;
                    }

                  case '1': // Meklē pasakumu pēc vārda 
                    system("clear");{ 
                    cout << "\n\033[1;34mSearch events\033[0m" << endl;
                    cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                    string eventName;
                    cout << "Enter the name of the event to search: ";
                    cin >> eventName;

                    bool foundEvent = false;

                    // Parbauda ja ir tāds pasākums
                    for (auto& e : events) {
                      if (e.name == eventName) { // Ja ir tad izvadās dati
                        foundEvent = true;
                        cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                        cout << "\033[1;32mEvent found\033[0m" << endl;
                        this_thread::sleep_for(chrono::seconds(5));
                        system("clear");

                        cout << "\n\033[34mSearch event by name\033[0m" << endl;
                        cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                        cout << "Name: " << e.name << endl;
                        cout << "Description: " << e.description << endl;
                        cout << "Cost: " << e.cost << endl;
                        cout << "Groups: \n";
                        for (auto& g : e.group) {
                          cout << g << ", ";
                        }
                        cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                        cout << "Press enter to return to the group search menu...";
                    
                            cin.ignore();
                            cin.get();
                            system("clear");
                        break;
                      }
                    }

                    if (!foundEvent) { // Kļūda, ja nav tāda pasākuma
                      cout << "\033[31mError: Event not found.\033[0m" << endl;
                      cout << "\033[31mYou need retry, with existing group\033[0m" << endl;
                      cout << "\nPress enter to return to the group search menu...";
                    
                          cin.ignore();
                          cin.get();
                          system("clear");
                    }
              break;
                    }

                  case '2': // Meklē pasakumu pēc grupas nosaukuma 
                    system("clear"); {
                    cout << "\n\033[1;34mSearch events\033[0m" << endl;
                    cout << "\033[1m------------------------------------------\n" << endl;
                    string groupName;
                    cout << "Enter the group name to search: ";
                    cin >> groupName;

                    bool foundEvent = false;

                    for (auto& e : events) {
                      for (auto& g : e.group) {
                        if (g == groupName) {
                          foundEvent = true;
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "\033[32mEvent found\033[0m" << endl;
                          this_thread::sleep_for(chrono::seconds(5));
                          system("clear");

                          cout << "\n\033[1;34mSearch event by groups name\033[0m" << endl;
                          cout << "\033[1m------------------------------------------\033[0m\n" << endl;
                          cout << "Name: " << e.name << endl;
                          cout << "Description: " << e.description << endl;
                          cout << "Cost: " << e.cost << endl;
                          cout << "Groups: \n";
                          for (auto& g : e.group) {
                          cout << g << ", ";
                          }
                          cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                          cout << "Press enter to return to the group search menu...";
                    
                              cin.ignore();
                              cin.get();
                              system("clear");
                          break;
                        }
                      }
                    }

                    if (!foundEvent) {
                      cout << "\033[31mError: Event not found.\033[0m" << endl;
                      cout << "\033[31mYou need retry, with existing group\033[0m" << endl;
                      cout << "\nPress enter to return to the group search menu...";
                    
                          cin.ignore();
                          cin.get();
                          system("clear");
                    }
                      break;
                  }
                
                  case '3': // Izvēle, kura atgriežās galvenāja izvēlne
                    system("clear"); {
                    ESearchChoice = '0';
                  
                    break;
                  default: {
                    system("clear");
                    cout << "\n\033[1;31mError: Invalid choice. Please try again.\033[0m" << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    system("clear");
                  }
                  }
              }
          break;
        }

            case '6': // Izvēle, var paskatīties pasākumu sarakstu
                system("clear");{

                // Izvade
                cout << "\n\033[34mEvent list\033[0m" << endl;
                cout << "\n\033[1m------------------------------------------\033[0m" << endl;
                for (const auto& event : events) {
                    cout << "\n" << event.name << endl;
                    cout << "\n\033[1mGroups: \033[0m";

                  //Parbauda vai ir grupa
                    bool hasGroups = false;
                    for (const auto& group : groups) {
                        if (group.name == group.name) {
                            cout << group.name << " ";
                            hasGroups = true;
                        }
                    }
                    if (!hasGroups) {
                        cout << "None";
                    }
                    cout << endl;
                }
                cout << "\n------------------------------------------" << endl;
                cout << "Press Enter to return to the main menu." << endl;
                cin.ignore();
                cin.get();
                system("clear");
                break;
            }
              
            case '7': // Izvēle, atgriežās galvenāja izvēlne
                system("clear"); {
                Echoice = '0';
                  
              break;
            default: {
            system("clear");
            cout << "\n\033[1;31mError: Invalid choice. Please try again.\033[0m" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("clear");
            }
                }
            }
          break;
        }

        case '5': // Ja lietotājs izvēlās "kopsavilkums"
            system("clear"); {
                printSummary(groups, teachers, students, events);
                cout << "Press enter to return to the previous menu...";
                        cin.ignore();
                        cin.get();

                        system("clear");
                        break;
                      }
                
        case '6': // Ja lietotājs izvēlās šo, tad programma beidzās
            system("clear"); {
            cout << "\033[1mGoodbye!\033[0m" << endl;
            cout << "\033[1;1m------------------------------------------\033[0m" << endl;
            cout << "\n\033[1;31mExiting...\033[0m\n" << endl;
            break;
        }
          
        default: { // Atkļūdošana ja lietotājs ievada nepareizu simbolu/ciparu
            system("clear");
            cout << "\n\033[1;31mError: Invalid choice. Please try again.\033[0m" << endl;
            this_thread::sleep_for(chrono::seconds(1));
            system("clear");
            }
               break;
          }
        } while (choice != '6'); // Viss pildās līdz kad izvēle ir 6

        // Aiztaisās .txt faili
        groupFile.close();
        teacherFile.close();
        studentFile.close();
        eventFile.close();
      
        return 0;
    }