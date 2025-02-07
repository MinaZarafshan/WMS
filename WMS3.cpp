#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
using namespace std ;
struct product{
	string fruit ;
	int price ;
	int num;
};
struct  member{
	string user , pass  ;
    int wallet ; 
};
int countLines(const string &filename) {
    ifstream file(filename);
  if (!file.is_open()) {
        cerr << "Unable to open file" << endl;
      return -1;
  }

  int lineCount = 0;
  string line;
  while (getline(file, line)) {
      lineCount++;
  }

  file.close();
  return lineCount;
}
string* readLines(const  string &filename, int lineCount, product* pru ) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file" <<   endl;
        return nullptr;
    }
    string* lines = new string[lineCount];
    string temp;
    for (int i = 0; i < lineCount; ++i) {
        temp="";
        getline(file, lines[i]);
        int len = lines[i].length() ;
        int j=0;
        int k=0;
        for (char chr : lines[i]){
            temp+=chr;
            k++;
            if(chr == ':'){
                temp.pop_back();
                pru[i].fruit=temp;
                j++;
                temp="";
            }
            if(chr == '-'){
                temp.pop_back();
                pru[i].price= stoi(temp);
                j++;
                temp="";
            }
            if(chr == '\0' || k == len){
                pru[i].num=stoi(temp);
                j++;
                temp="";
            } 
        }
    }
    file.close();
    delete[] lines;
    return lines;
}
int being_member(string username , string password , member* members  ){
	int i = 0;
    for( i= 0 ; i<5 ; i++){
        if(username==members[i].user && password==members[i].pass ){
            return i ;
        }
    }
    if(i==5){
    	return i;
	}

}
void show(product* pru , int lineCount , string temp , string command){
    int i = 0 ;
    for( i = 0 ; i<lineCount ; i++){
        
        if( command=="show "+pru[i].fruit){
            cout <<"\nthere are "<< pru[i].num << " " << pru[i].fruit << ". each of them costs " << pru[i].price<<"." <<endl;
            break ;
        }
    }
    if(command == "show item"){
        for(int j = 0 ; j<lineCount ; j++){
            cout << pru[j].fruit<< endl ;
            i=0 ;
        }
    }
    if(i==lineCount){
        cout<<"\nthis item is not exist!\n" ;
    }
}
void buy(product* pru , int lineCount , string command , int which , member* members , bool& successful_buying){
    int i=0 ;
    for(i = 0 ; i<lineCount ; i++){
        if("buy "+ pru[i].fruit == command ){

            if(pru[i].num >= 1){
                if(members[which].wallet>=pru[i].price ){
                    pru[i].num-=1;
                    members[which].wallet-=pru[i].price ;
                    cout << "\nyour purchase eas successful .\n" ;
                    successful_buying = true ;
                    i=0;
                    break ;
                }
                else if(members[which].wallet<pru[i].price){
                    
                    cout << "\nyour acount balance is not sufficient.\n";
                    i = 0;
                    break ;
                }
                //else{
                  //  cout << "your request is incorrect. please try again\n" ;
                //}
            }
            else{
                cout << "there is no enough amount of this number in the store\n" ;
                break ;
            }
        }
        if(i == lineCount-1){
            cout <<"this item is unavailble " ; 
        }
        
    }

}
void balance (member* members , int which){
    cout <<"\nyour account balance is :"<< members[which].wallet<< "$\n" ;

}
void help(string command , int lineCount  ){
    if(command =="help show" ){
        cout<<"you can see items in the stor by entering, show item. And if you want to know details of an item you should enter show fruitname\n";
    }
    else if(command=="help buy"){
        cout <<"you can buy every item you want by entering , buy fruitname\n";
    }
    else if(command == "help balance"){
        cout << "you can see your wallet if you just enter wallet.\n" ;
    }
    else if(command == "help command" ){
        cout << "\nif you want to know about any special item you can use this item.\n " ;
    }
    else{
        cout << "\nyour request is not availble.\n ";
    }
}
void add(string command , product*& pru, product& newpru , int& lineCount, bool& successful_add ){
    string additem ;
    
    for (int i = 4 ; i<command.length() ; i++){
                        
        additem+=command[i] ;
    }
    string newfruit , newprice ;
    
    for (char chr : additem){           
        if(chr>=97 && chr<=122){                            
            newfruit+=chr;
        }
        else if(chr>=48 && chr<=57){
            newprice+=chr;
        }
    }
    
    
    newpru = {newfruit , stoi(newprice) , 1 } ; 
    int newsize = lineCount +1 ;
    product* newprus = new product[newsize] ;
    for(int i = 0 ; i<lineCount ; i++){
        newprus[i]=pru[i];
    }    
    newprus[lineCount] = newpru ;
    successful_add = true ;

    cout << "addition successful";
    delete [] pru ;
    
    pru = newprus ;
    lineCount +=1 ;
    //delete[] newprus ;

}
void remove (product*& pru , int& size  , product& beremoved , string command){


    int newsize = size -1 ;
    product* newpru = new product[newsize];
    int j = 0 ;
    for(int i = 0 ; i<size; i++){
        if(command != "remove " + pru[i].fruit){
            newpru[j]=pru[i] ;
            j++ ;
        }
        else if(command == "remove " + pru[i].fruit){
            beremoved = pru[i] ;
            cout<<"\n this item removed successfully\n" ;

        }
    }

    delete[] pru ;
    pru = newpru ;
    size = newsize ;
}
void rename(product* pru , string command , int size ){
    string secpart , thirdpart;
    for(int i = 7 ; i<command.length() ; i++){
            secpart+=command[i] ;
        }
    for(int i = 0 ; i<secpart.length()-1 ; i++){
            if(secpart[i]==32){
                int j =i+1 ;
                for(j ; j<secpart.length() ; j++){
                    thirdpart+=secpart[j] ;

                }
                break ;
            }
        //    if(secpart[i]==32){
          //      break ;
            }
  //  }
    
    for(int i = 0 ; i<size ; i++){
        
        if(command == "rename "+ pru[i].fruit +" "+ thirdpart){
          pru[i].fruit = thirdpart ;
          cout << "done!" ;
          
        }
    }
    
}
void price (string command , product* pru , int size ) {
    string changeprice ;
    
    for (int i = 6 ; i<command.length() ; i++){
                        
        changeprice+=command[i] ;
    }
    
    string fruit , updateprice ;
    
    for (char chr : changeprice){           
        if(chr>=97 && chr<=122){                            
            fruit +=chr;
        }
        else if(chr>=48 && chr<=57){
            updateprice+=chr;
        }
    }
    for(int i = 0 ;i <size ; i++){
        if (pru[i].fruit == fruit){
            pru[i].price = stoi(updateprice);
            break ;
        }
        if(i == size-1){
            cout << "\nthis item is unavailble!\n" ;
        }
    }
    
}
void credit(member* members , string command ){
    string userbalance ;
    
    for (int i = 7 ; i<command.length() ; i++){
                        
        userbalance+=command[i] ;
    }
    cout << userbalance ;
    string user , wallet ;
    for(int i = 0 ; i< userbalance.length() ; i++){
        if(userbalance[i]!=32){
            user+=userbalance[i];
        }
        if(userbalance[i]==32){
            break ;
        }
    }

    int size = user.length();
    for(int i = size+1 ; i<userbalance.length() ; i++){
        wallet+=userbalance[i] ;
    }
   
    for(int i =0 ; i<5 ; i++){
       if( members[i].user == user){
            members[i].wallet += stoi(wallet) ;
       }
    }
    

} 
void ProductsChanges(product* pru , int size){
    ofstream myFile ;
    myFile.open("WMS.txr" , ios :: out);
    if(myFile.is_open()){
        for (int i = 0 ; i<size ; i++){
            myFile.flush()<< pru[i].fruit << ": " << pru[i].price << "- " << pru[i].num << endl;
        }
        myFile.close();
    }
    else{
        cerr << "error ! " ;
    }
    
}   
void capitaltosmall(string& name){
    for(int i = 0 ; i<name.length() ; i++){
            name[i] = tolower(name[i]);
          }
}
void ctrlZ(product*& pru ,int& size , product& beremoved ){
    int newsize = size +1 ;
    product* befor = new product[newsize] ;
    for(int i = 0 ; i<size ;i++){
        befor[i]=pru[i];
    }
    befor[size]= beremoved ;
    beremoved.fruit="0"; 
     delete [] pru ;
    pru = befor ;
    size = newsize ;
    
}        
  















int main(){
    member members[5];
    string filename = "WMS.txt";
    int lineCount ;
    bool successful_add = false ;
    bool successful_buying = false;
    lineCount = countLines(filename );
    product* pru = new product[lineCount];
    int j = 0 ;
    readLines(filename, lineCount, pru );
    product newpru ;
    product beremoved = {"0", 0, 0} ;
    members[0].user ="admin1" ;
    members[0].pass = "admin1_pass" ;
    members[1].user ="admin2" ;
    members[1].pass = "admin2_pass" ;
    members[2].user ="non-admin1" ;	
    members[2].wallet = 700 ; 
    members[2].pass = "member1pass" ;
    members[3].user ="non-admin2" ;
    members[3].wallet =	500 ;
    members[3].pass = "member2pass" ;
    members[4].user ="non-admin3" ;	
    members[4].wallet = 800 ;
	members[4].pass = "member3pass" ;
    string username , password ;



    while(true){
        int which ;
        cout << "please enter your username: " ;
	    cin>> username ;
        capitaltosmall(username);
	    cout << "please enter your password: " ;
	    cin >> password ;
        capitaltosmall(password);
        which =being_member(username , password , members);
        string name ;
	    if (which>= 0 && which<= 4  ){
	    	cout<< "welcom to your panel!"<<members[which].user ;
	    	//break;
    	}
	    else{
		     cout << "sorry , your username or your password is wrong! please try again. "<< endl ;
		     continue;
    	}

        while(true){

            if (which>=2 && which<=4){
                string name ;
                cout << "\n what do you want?\n" ;
                cout << "menu : \n" << "1.show ITEM\n 2.buy ITEM \n 3.balance \n 4.help COMMAND \n 5.exit\n ";
                string command ;
                cout <<"which item?\n" << "# " ;
                
			    cin.ignore();
                getline(cin , command);
                capitaltosmall(command);
                string temp ;
                for(int i = 0 ; i<command.length() ; i++){
                    if(command[i]==' '){
                        break ;
                    }
                    else{
                        temp+=command[i] ;
                    }
                    
                }

                if(temp == "show"){
                    show(pru , lineCount , temp , command);
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            
                    }
                    else if(req == "no"){
                        break ;
                    }    
                }
                else if(temp == "buy"){
                    buy(pru , lineCount , command , which , members , successful_buying);
                    if (successful_buying ){
                        ProductsChanges(pru , lineCount);
                    }
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    
                }
                else if(command == "balance"){
                    balance(members , which);
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    
                }
                else if(temp == "help"){
                    help(command , lineCount ) ;
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    
                }
                else if(command == "exit"){
                    break ;
                }
                else{
                    cout << "your request isnt exist!" ;
                    continue;
                }
            }
            else{
                string name ;
                cout << "\n what do you want?\n" ;
                cout << "menu : \n" << "1.add item\n 2.remove item \n 3.rename item to newitem \n 4.price item newprice \n 5.credit user amount \n 7.return item \n 6.exit\n ";
                
                string command ;
                cout <<"which item?"<<endl<< "$ " ;
			    cin.ignore();
                getline(cin , command);
                capitaltosmall(command);
                string temp ;
                for(int i = 0 ; i<command.length() ; i++){
                    if(command[i]==' '){
                        break ;
                    }
                    else{
                        temp+=command[i] ;
                    }
                }
                
                if(temp == "add"){
                    
                    add(command , pru,  newpru , lineCount , successful_add );
                    if(successful_add){
                        ProductsChanges(pru , lineCount);
                    }
                    
                    
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            
                    }
        
                    else if(req == "no"){
                        break ;
                    }    
                }
                else if(command == "return"){
                    if(beremoved.fruit != "0"){
                        ctrlZ(pru , lineCount , beremoved);
                        ProductsChanges(pru , lineCount);
                        cout << "\ndone!\n" ;
                    }
                    else{
                        cout << "you havent removed an item yet" ;
                    }
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    

                }
                else if(temp == "remove"){
                    remove(pru , lineCount , beremoved , command);
                    ProductsChanges(pru , lineCount);
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    
                }
                else if(temp == "rename"){
                    rename(pru , command , lineCount );
                    ProductsChanges(pru , lineCount);
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    
                   
                }
                else if(temp == "price"){
                    price (command , pru , lineCount );
                    ProductsChanges(pru , lineCount);
                    //for(int i = 0 ; i<lineCount ; i++){
                      //  cout << pru[i].fruit << pru[i].price << pru[i].num ;
                   // }
                   string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    
                }
                else if(temp == "credit"){
                    credit(members , command);
                    cout << "\ndo you want to check members wallet?\n";
                    string yesno ;
                    cin>> yesno ;
                    if(yesno == "yes"){
                        for(int i = 2 ; i<5 ; i++){
                            cout <<endl <<members[i].user << " : " << members[i].wallet<< endl ;
                        }
                    }
                    
                    //cout << members[2].user << endl << members[2].wallet ;
                    string req ;
                    cout<<"\nany other request?\n ";
                    cin >> req ;
                    capitaltosmall(req);
                    if(req=="yes"){
                        continue;            ;
                    }
                    else if(req == "no"){
                        break ;
                    }    
                }
                
                else if(temp == "exit"){
                    break ;
                }



            }


        }

    }


return 0 ;
}