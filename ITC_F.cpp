#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <vector>
#include <queue>

using namespace std;
float probTable[100];
int lengthTable[100],iii;
string convert_tobinary(double num, int k_prec)
                    {
                        string binary = "";
                        int Integral = num;
                        double fractional = num - Integral;
                        while (Integral) {
                            int rem = Integral % 2;
                        binary.push_back(rem +'0');
                        Integral /= 2;
                    }
                    reverse(binary.begin(),binary.end());
                    binary.push_back('.');
                    while (k_prec--)
                    {
                        fractional *= 2;
                        int fract_bit = fractional;
                        if (fract_bit == 1)
                        {
                            fractional -= fract_bit;
                            binary.push_back(1 + '0');
                        }
                        else
                            binary.push_back(0 + '0');
                    }
                    return binary;
                    }
/*struct Node {
    int key;
    Node* left, *right;
};

Node* newNode(int key)
{
    Node* node = new Node;
    node->key = key;
    node->left = node->right = NULL;
    return (node);
}
int addBT(Node* root)
{
    if (root == NULL)
        return 0;
    return (root->key + addBT(root->left) + addBT(root->right));
}*/
struct node {
    string sym;
    float pro;
    int arr[20];
    int top;
} prr[20];

typedef struct node node;

void sh1(int l, int h, node prr[])
{
    float pp1 = 0, pp2 = 0, diff1 = 0, diff2 = 0;
    int i, d, k, j;
    if ((l + 1) == h || l == h || l > h) {
        if (l == h || l > h)
            return;
        prr[h].arr[++(prr[h].top)] = 1;
        prr[l].arr[++(prr[l].top)] = 0;
        return;
    }
    else {
        for (i = l; i <= h - 1; i++)
            pp1 = pp1 + prr[i].pro;
        pp2 = pp2 + prr[h].pro;
        diff1 = pp1 - pp2;
        if (diff1 < 0)
            diff1 = diff1 * -1;
        j = 2;
        while (j != h - l + 1) {
            k = h - j;
            pp1 = pp2 = 0;
            for (i = l; i <= k; i++)
                pp1 = pp1 + prr[i].pro;
            for (i = h; i > k; i--)
                pp2 = pp2 + prr[i].pro;
            diff2 = pp1 - pp2;
            if (diff2 < 0)
                diff2 = diff2 * -1;
            if (diff2 >= diff1)
                break;
            diff1 = diff2;
            j++;
        }
        k++;
        for (i = l; i <= k; i++)
            prr[i].arr[++(prr[i].top)] = 0;
        for (i = k + 1; i <= h; i++)
            prr[i].arr[++(prr[i].top)] = 1;
        sh1(l, k, prr);
        sh1(k + 1, h, prr);
    }
}

void sortByProbability(int nn1, node prr[])
{
    int i, j;
    node tmmp;
    for (j = 1; j <= nn1 - 1; j++) {
        for (i = 0; i < nn1 - 1; i++) {
            if ((prr[i].pro) > (prr[i + 1].pro)) {
                tmmp.pro = prr[i].pro;
                tmmp.sym = prr[i].sym;

                prr[i].pro = prr[i + 1].pro;
                prr[i].sym = prr[i + 1].sym;

                prr[i + 1].pro = tmmp.pro;
                prr[i + 1].sym = tmmp.sym;
            }
        }
    }
}

void display(int nn1, node prr[])
{
    int i, j;
    float h22,l22;
    cout << "\n\nSymbol\tProbability\tCode\tLength";
    for (i = nn1 - 1; i >= 0; i--) {
        cout << "\n" << prr[i].sym << "\t\t" << prr[i].pro << "\t";
        for (j = 0; j <= prr[i].top; j++)
            cout << prr[i].arr[j];
        cout <<"\t"<<prr[i].top+1;
    }

    cout<<"\n\nStep 5: Finding Code Efficiency\n";
        h22 = 0;
        l22 = 0;
        for (int i=1;i<=nn1;i++)
        {
            h22 += prr[i-1].pro*log2(1/prr[i-1].pro);
            l22 += prr[i-1].pro*(prr[i-1].top+1);
        }
        cout<<"\n\n";
        cout<<"H(s)                 = "<<h22<<"\n"<<"L                    = "<<l22<<"\nCode Efficiency      = "<<(h22/l22)*100<<" %"<<"\nCode Redundancy      = "<<100-((h22/l22)*100)<<" %";


}

class HFMN
{
 struct New_Node
 {
  char data;
  size_t freq;
  New_Node* left;
  New_Node* right;
  New_Node(char data, size_t freq) : data(data),
                                 freq(freq),
left(NULL),
right(NULL)
                                 {}
 ~New_Node()
 {
   delete left;
   delete right;
 }
 };

 struct compare
 {
  bool operator()(New_Node* l, New_Node* r)
  {
    return (l->freq > r->freq);
  }
};

New_Node* top;

void print_Code(New_Node* root, string str)
{
    float temp4;
if(root == NULL)
   return;

 if(root->data == '$')
 {
  print_Code(root->left, str + "0");
  print_Code(root->right, str + "1");
 }
 if(root->data != '$')
 {
    temp4 = ((root->freq)) * 0.001;
    probTable[iii]= temp4;
    lengthTable[iii] = str.length();

   iii+=1;
   cout << root->data<<"\t\t" << str << "\t\t"<< str.length()<<"\t\t"<< temp4 << "\n";
   print_Code(root->left, str + "0");
   print_Code(root->right, str + "1");
 }
}

public:
  HFMN() {};
  ~HFMN()
  {
    delete top;
  }
  void HFMN_TR(vector<char>& data, vector<size_t>& freq, size_t size)
  {
   New_Node* left;
   New_Node* right;
   priority_queue<New_Node*, vector<New_Node*>, compare > minHeap;

for(size_t i = 0; i < size; ++i)
   {
      minHeap.push(new New_Node(data[i], freq[i]));
   }

while(minHeap.size() != 1)
    {
      left = minHeap.top();
minHeap.pop();

      right = minHeap.top();
minHeap.pop();

      top = new New_Node('$', left->freq + right->freq);
      top->left  = left;
      top->right = right;
      minHeap.push(top);
     }
    cout<<"\n\nSymbols\t\tCodes\t\tLength\t\tProbability\n";
    iii = 0;
    print_Code(minHeap.top(), "");
 }
};

//by:
//ROHIT D HEGDE (DVRBLACKTECH)
//4CB18EC055
//pH nO: 9448803740

int main() {
       int selection,temp,nth_ext_symbols,trueFlag,cont,exten_temp,i1;
       string se;
       int no_s,i,exten,j,no_symbols,z;
       float p[100],entropy=0,s_rate,res[100],entropy_res[100];


       float prob[100][100],h[100],H,G[100],ress;
       int y,cont1,cont2,zz;

       float p_copy[100],alpha[100],l[100],h22,l22;
       int n1,binl[100];
       string bin[100];

       int nn1;
       float total = 0;
       string ch;
       node tmmp;

       int n, f;
       float f1;
       char ch11;
       HFMN set1;
       vector<char> data;
       vector<size_t> freq;




       start:
       cout << "SELECT YOUR CHOICE:\n\n";

       cout << "1. INFORMATION CONVEYED \n";
       cout << "2. MARKOV MODEL \n";
       cout << "3. SHANNON'S ENCODING ALGO. \n";
       cout << "4. SHANNON FANO ENCODING ALGO. \n";
       cout << "5. HUFFMAN ENCODING ALGO. \n\n";


       cin >> selection;

       switch (selection) {
            case 1:
                ////////////////////////////////////////////////////////////////////////////////
                inf_con:
                cout << "\n1. Enter the no. of symbols and it's probabilities: ";
                cin >> no_s;

                for (i = 0; i < no_s; i++) {
                        cin >> p[i];
                }
                cout << "\n2. Enter the symbol rate \(if not type '0'\): ";cin >> s_rate;
                cout << "\n3. Enter the extension of the source: ";cin >> exten;

                cout << setw(7) << "Sl. No:" << setw(15) << "Symbols" << setw(15) << "Probability" << setw(24) << "Information Conveyed"<< endl << endl;
                cout << setw(7+15+15+24) << "BITS" << setw(12) << "HARTLEY" << setw(12) << "NATS"  << endl << endl;
                for (int i = 0; i < no_s; i++) {
                        entropy += p[i]*(log2(1/p[i]));
                        cout << setw(7) << i+1 << setw(15) << i+1   << setw(15) << p[i]  << setw(24) << log2(1/p[i]) << setw(12) << log10(1/p[i]) << setw(12) << log(1/p[i])  << endl << endl;
                }



                cout << "\nEntropy of Source:" << entropy <<"  bits/message symbol\n";
                cout << "\nAvg Information rate of Source:" << entropy*s_rate <<"  bits/sec\n";
                cout << "\nEfficiency of Source:" << (entropy/log2(no_s))*100 <<" %\n";
                cout << "\nRedundancy of Source:" << 100-((entropy/log2(no_s))*100) <<" %\n";


                ///////////////////////////////////nth order/////////////////////////////////////////
                if (exten>1){

                for (int k = 2;k <= exten; k++){
                for (i = 0; i < 100; i++){res[i]=1;}
                nth_ext_symbols = pow(no_s, k);
                cout << "\n\n\nNo of symbols in :" << k <<" extension : "<< nth_ext_symbols ;
                cout <<"\n"<<"Intermediate Probabilities";
                exten_temp = k;

                for (int i1=0;i1<=exten_temp;i1++){
                //cout << "outer while";
                cout << "\n";
                z = 0;
                cont = 0;
                exten_temp = exten_temp - i1;
                trueFlag = 1;
                while (trueFlag==1)
                {   //cout << "inner while";
                    for (int i = 0; i < nth_ext_symbols; i++)
                        {
                            res[i] = res[i] * p[z];
                            cout << p[z] << "  ";
                            //prob[k][i] = p[z];
                            cont+=1;
                            if (cont==pow(no_s, i1))
                            {
                                z=z+1;
                                cont = 0;
                            }
                            if (z==no_s){
                                z = 0;
                                cont = 0;
                            }
                        //cout << res[i] << "  ";
                       }
                    trueFlag = 0;
                }
                }

                entropy = 0;
                cout <<"\n\nSymbol Probabilities\n";
                for (int i = 0; i < nth_ext_symbols; i++) {

                        cout << res[i] << "  ";
                        entropy += res[i]*(log2(1/res[i]));
                    }


                entropy_res[k] = entropy;
                cout<<"\n\nEntropy = "<<entropy;
                }



                }














                /////////////////////////////////////////////////////////////////////////////////

                cout << "\n\nb: BACK    ||    e:EXIT       ||    m: MAIN MENU";
                cin >> se;

                if (se == "e")
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }

                else if (se == "b")
                    {
                        goto inf_con;
                    }
                else if (se == "m")
                    {
                        goto start;
                    }

                else
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }
                break;

//by:
//ROHIT D HEGDE (DVRBLACKTECH)
//4CB18EC055
//pH nO: 9448803740
            case 2:
                markov:

                cout << "\n1. Enter the no. of symbols and it's probabilities: ";
                cin >> no_s;

                for (i = 0; i < no_s; i++)
                {
                    cin >> p[i];
                }
                cout << "Enter path probability \n";
                for (i = 1; i <= no_s; i++)
                {
                    for(int j=1; j<=no_s; j++)
                    {
                        cout << "Enter the probability of : " << i << " --> " << j << " :";
                        cin >> prob[i][j];

                    }
                 }
                 cout<<"Enter the source extension:  ";
                 cin>>exten;

                 cout<<"\nEntropy of Each State:\n";
                 for (i = 0; i < 100; i++){h[i]=0;}
                 for (i = 1; i <= no_s; i++)
                 {
                     for(int j=1; j<=no_s; j++)
                     {
                         h[i] +=  prob[i][j]*(log2(1/prob[i][j]));
                     }
                     cout<<"H"<<i<<" : "<<h[i]<<"\n";
                 }

                 H=0;
                 for (i = 0; i < no_s; i++)
                 {
                     H+=p[i]*h[i+1];
                 }
                 cout<<"\nEntropy of Source: "<<H<<"  Bits/MessageSymbol\n\n";


                 cout<<"Gn = 1/N SUM i=1 to n p(mi) log2 1/p(mi)";
                 G[1] = 0;
                 for (i = 0; i < no_s; i++)
                 {
                     G[1]+= p[i]* log2(1/p[i]);
                 }
                 cout << "\nG1 = "<<G[1]<<" bits/message symbol";

                 //////rohitDH//////

            for (int k = 2;k <= exten; k++){
                for (i = 0; i < 100; i++){res[i]=1;}
                nth_ext_symbols = pow(no_s, k);
                cout << "\n\n\n\nNo of symbols in :" << k <<" extension : "<< nth_ext_symbols ;
                cout <<"\n"<<"Intermediate Probabilities\n";
                exten_temp = k;

            for (int i1=0;i1<=exten_temp-2;i1++){
                    cout<<"\nRepeat: "<<i1<<"\n";
                z = 0;
                cont = 0;
                cont1=0;
                y=1;
                //exten_temp = exten_temp - 1; //1
                trueFlag = 1;
                while (trueFlag==1)
                {
                    for (int i = 0; i < nth_ext_symbols; i++)
                    {
                        res[i] = res[i] * prob[z+1][y];
                        cout << prob[z+1][y] << "  ";
                        cont +=1;cont1+=1;
                        if (cont1==pow(no_s, i1))
                        {
                           y = y+1;
                           cont1=0;
                        }
                        if (cont==pow(no_s, i1+1))
                        {
                            z=z+1;
                            cont = 0;
                        }
                        if (z==no_s){
                            z=0;
                            cont = 0;
                        }

                        if (y==no_s+1){
                            y=1;
                        }
                    }
                    trueFlag = 0;
                }
                cout<<"\n\n";
            }

            zz = 0;
                cont2 = 0;
                for (int z=0;z<nth_ext_symbols;z++)
                {
                    cout << p[zz] << "  ";
                    res[z] = res[z] * p[zz];
                    cont2 +=1;
                    if(cont2==nth_ext_symbols/no_s)
                    {
                        zz+=1;
                        cont2 = 0;
                    }
                    if(zz>=no_s)
                    {
                        zz = 0;
                    }
                }
                cout <<"\n\nSymbol Probabilities\n";
                G[k] = 0;
                ress = 0;
                for (int zz=0;zz<nth_ext_symbols;zz++)
                {
                    cout<<res[zz]<<" ";
                    ress += res[zz]* log2(1/res[zz]);
                }
                cout<<"\nSummation Result:  "<<ress;
                G[k] = ress/k;
                cout<<"\nG" <<k<<" = "<<G[k];
            }


                ////RohitDH///






                /////////////////////////////////////////////////////////////////////////////////

                cout << "\n\nb: BACK    ||    e:EXIT     ||    m: MAIN MENU";
                cin >> se;

                if (se == "e")
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }

                else if (se == "b")
                    {
                        goto markov;
                    }

                else if (se == "m")
                    {
                        goto start;
                    }

                else
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }
                break;

//by:
//ROHIT D HEGDE (DVRBLACKTECH)
//4CB18EC055
//pH nO: 9448803740
            case 3:
                shannon:
                    ///////////////////////////////////////////////////////////////////////////////////////////////
                    cout << "\n1. Enter the no. of symbols and it's probabilities: ";
                    cin >> no_s;

                    for (i = 0; i < no_s; i++)
                    {
                        cin >> p[i];
                        p_copy[i] = p[i];
                    }

                    //1
                    cout<<"\n\nStep 1: Sorting in Decreasing Order\n";
                    n1 = sizeof(p)/sizeof(p[0]);
                    sort(p, p+n1, greater<float>());
                    for (int i = 0; i < no_s; i++)
                        cout << p[i] << " ";


                    //2
                    cout<<"\n\nStep 2: Finding Alpha\n";
                    alpha[1] = 0;
                    for (int i = 2;i<=no_s+1;i++)
                    {
                        alpha[i] = alpha[i-1] + p[i-2];
                    }
                    for (int i = 1; i <= no_s+1; i++)
                        cout << "alpha "<<i<<" = "<< alpha[i] << "\n";

                    //3
                    cout<<"\n\nStep 3: Finding Length of Respective Probability\n";

                    for (int i=1;i<=no_s;i++)
                    {   j = 0;
                        while(pow(2,j)<(1/p[i-1]))
                        {
                            j+=1;
                        }
                        l[i] = j;
                    }
                    for (int i=1;i<=no_s;i++)
                    {
                        cout << "L"<<i<<" = "<< l[i] << "\n";
                    }

                    //4
                    cout<<"\n\nStep 4: Finding Alpha i in binary form till length Li\n";
                    for (int i=1;i<=no_s;i++)
                    {
                        bin[i] = convert_tobinary(alpha[i], l[i]);
                    }
                    for (int i=1;i<=no_s;i++)
                    {
                        cout << "L"<<i<<" = "<< l[i] <<setw(10)<< "alpha "<<i<<" = "<< alpha[i] <<setw(20)<<"Code "<<i<<" = "<< bin[i].substr(1,bin[i].length())<< "\n";
                    }

                    //5
                    cout<<"\n\nStep 5: Finding Code Efficiency\n";
                    h22 = 0;
                    l22 = 0;
                    for (int i=1;i<=no_s;i++)
                    {
                        h22 += p[i-1]*log2(1/p[i-1]);
                        l22 += p[i-1]*l[i];
                    }
                    cout<<"\n\n";
                    cout<<"H(s)                 = "<<h22<<"\n"<<"L                    = "<<l22<<"\nCode Efficiency      = "<<(h22/l22)*100<<" %"<<"\nCode Redundancy      = "<<100-((h22/l22)*100)<<" %";

                    ///////////////////////////////////////////////////////////////////////////////////////////////
                cout << "\n\nb: BACK    ||    e:EXIT       ||    m: MAIN MENU";
                cin >> se;

                if (se == "e")
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }

                else if (se == "b")
                    {
                        goto shannon;
                    }

                else if (se == "m")
                    {
                        goto start;
                    }

                else
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }
                break;


//by:
//ROHIT D HEGDE (DVRBLACKTECH)
//4CB18EC055
//pH nO: 9448803740
            case 4:
                shannon_fano:
                    ///////////////////////////////////////////////////////////////////////////////////////////
                cout << "Enter number of symbols : ";
                cin>>nn1;
                for (i = 0; i < nn1; i++)
                {
                    ch = (char)(65 + i);
                    prr[i].sym += ch;
                }
                float x[100];
                cout << "Enter probability values : ";
                for (i = 0; i < nn1; i++)
                {
                    cin>>x[i];
                    prr[i].pro = x[i];
                }
                prr[i].pro = 1 - total;
                sortByProbability(nn1, prr);
                for (i = 0; i < nn1; i++)
                    prr[i].top = -1;
                sh1(0, nn1 - 1, prr);
                display(nn1, prr);
                    //////////////////////////////////////////////////////////////////////////////////////////

                cout << "\n\nb: BACK    ||    e:EXIT      ||     m:MAIN MENU";
                cin >> se;

                if (se == "e")
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }

                else if (se == "b")
                    {
                        goto shannon_fano;
                    }

                else if (se == "m")
                    {
                        goto start;
                    }

                else
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }
                break;

//by:
//ROHIT D HEGDE (DVRBLACKTECH)
//4CB18EC055
//pH nO: 9448803740
            case 5:
                huffman:
                    //////////////////////////////////////////////////////////////////////////////////////////
                    {cout<<"Enter the number of elements \n";
                    cin>>n;
                    for (int i=0;i<n;i++)
                    {
                        ch11 = (char)(65 + i);
                        data.insert(data.end(), ch11);
                    }
                    cout<<"Enter the probability of symbols \n";
                    for (int i=0;i<n;i++)
                    {
                        cin>>f1;
                        f = (int)(f1*1000);
                        freq.insert(freq.end(), f);
                    }

                    size_t size = data.size();
                    set1.HFMN_TR(data, freq, size);

                    cout<<"\n\n Finding Code Efficiency";
                    h22 = 0;
                    l22 = 0;
                    for (int i=1;i<=n;i++)
                    {
                        h22 += probTable[i-1]*log2(1/probTable[i-1]);
                        l22 += probTable[i-1]*lengthTable[i-1];
                    }
                    cout<<"\n";
                    cout<<"H(s)                 = "<<h22<<"\n"<<"L                    = "<<l22<<"\nCode Efficiency      = "<<(h22/l22)*100<<" %"<<"\nCode Redundancy      = "<<100-((h22/l22)*100)<<" %";

                    //////////////////////////////////////////////////////////////////////////////////////////
                    }
                    cout << "\n\nb: BACK    ||    e:EXIT     ||     m:MAIN MENU";
                    cin >> se;

                if (se == "e")
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }

                else if (se == "b")
                    {
                        goto huffman;
                    }

                 else if (se == "m")
                    {
                        goto start;
                    }

                else
                    {
                        cout << "...THANK YOU...";
                        exit(0);
                    }

                break;

            default:
                cout << "Enter Valid Selection\n";
                goto start;
    }
   return 0;
}
