#include "PCPProgram.h"

using namespace PCPProgram;
int main(int args, char *in[]) {
   //DominoProgram::isSolution(*temp);
   //cout << "Calling Run\n";

   PCPSolver::run("fileName.txt");

/*
   string s1 = "abbabaabb";
   string s2 = "abbabaabb";
   string s3 = "abbaba";
   string s4 = "aabb";
   cout << "result s1.find(s2): " << s1.find(s2) << endl;   
   cout << "result s1.find(s3): " << s1.find(s3) << endl;   
   cout << "result s1.find(s4): " << s1.find(s4) << endl;   
   cout << "result s2.find(s1): " << s1.find(s2) << endl;   
*/


   return 0;
}
