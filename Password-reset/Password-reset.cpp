#include <bits/stdc++.h>
using namespace std;
bool canw_f(const string& filename){
    ofstream file(filename,ios::app);
    if(file){
        file.close();
        return 1;
    }
    return 0;
}
int main(){
	if(canw_f("C:\\ProgramData\\Hitmux\\data.hit")){
		system("del C:\\ProgramData\\Hitmux\\data.hit");
		printf("Password reset successful!");
	}
	else printf("Some unknown errors occurred.\nPlease try to re-run the software with administrator rights.\nOr contact caokai674@gmail.com.");
	getchar();
	return 0;
}