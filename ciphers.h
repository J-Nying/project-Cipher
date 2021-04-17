using namespace std;

string caesarCipher(string s, int k){

    string print;
    char c;

    for (int i = 0; i < s.length(); i++) {
        c=s[i];
        if(c>='a' && c<='z'){
            c=s[i]+k;
            if(c>'z'){
                print+= c + 'a' - 'z' - 1;
            }
            else{
                print+=c;
            }
        }

        else if(c>='A' && c<='Z'){
            c=s[i]+k;
            if(c>'Z'){
                print+= c + 'A' - 'Z' - 1;
            }
            else{
                print+=c;
            }
        }
        else{
            print+=c;
        }
    }

    return print;
}









string railFenceCipher(string s, int k){

    bool goingDown=true;
    string finalString="";
    
    char array[k][s.length()];
    for(int i=0; i<k; i++){
        for(int j=0; j<s.length(); j++){
            array[i][j]='|';
        }
    }
    
    int row=0;
    int column=0;

    for(int i; i<s.length(); i++){
        
        if(goingDown){
            array[row][column]=s[i];
            row++;
            if(row>=k-1){
                goingDown=false;
                column++;
            }
        }
        else{
            array[row][column]=s[i];
            row--;
            if(row==0){
                goingDown=true;
                column++;
            }
        }
        


    }

    for(int j=0;j<k; j++){
        for(int k=0; k<s.length(); k++){
            if(array[j][k]!='|')
            finalString+=array[j][k];
        }
    }

    return finalString;
}




string simpleSubstitutionCipher(string s, string k){

    int getKey;

    for(int i=0; i<s.length(); i++){
        if('a'<=s[i] && s[i]<='z' || 'A'<=s[i] && s[i]<='Z' || '0'>=s[i] && s[i]>='9'){
            if(islower(s[i])){
                getKey = s[i]-'a';
                s[i] = k[getKey];
            }
            else{
                getKey = s[i]-'A';
                s[i] = toupper(k[getKey]);
            }
        }
    }


    return s;
}





string atbashCipher(string s){   
    for(int i=0; i<s.length(); i++){
        if('a'<=s[i] && s[i]<='z' || 'A'<=s[i] && s[i]<='Z' || '0'>=s[i] && s[i]>='9'){
            if(islower(s[i])){
                s[i] = 'z' - s[i] + 'a';
            }
            else{
                s[i] = 'Z' - s[i] + 'A';
            }
        }
    }
    return s;
}


