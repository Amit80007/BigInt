#ifndef HW8_H_
#define HW8_H_
#include<vector>
#include<iostream>
#include<string>

using namespace std;

class BigInt{
public:
	int size;
	char* charArray=nullptr;
	vector<int> intVec;

	BigInt(){}

	BigInt(vector<int> vec){
		this->intVec=vec;
		this->size=vec.size();
		this->charArray=new char();
		int j=0;
		int i=0;


		for(i=1;i<vec.size();i++)
		{
			if(vec[i]>=0 && vec[i]<=9){
				this->charArray[i]=vec[i];
			}else{

				cerr << "Invalid input";
				return;
				break;
			}
		}

		this->charArray[i]='\0';
	}
	BigInt(vector<char> vec){
		this->size=vec.size();
		vector<int>& tmp =this->intVec;
		tmp.reserve(this->size);
		int k=0;
		if(vec[0]==43 || vec[0]==45){
			if(vec[0]==45){
				if(vec[1]>=48 && vec[1]<=57){
					int x=vec[1];
					x=x-48;
					tmp.push_back(x*(-1));
					k=2;
				}else{
					cerr << "Invalid Input";
					return;
				}

			}else{
			k=1;}
		}

		for(int i=k;i<vec.size();i++)
				{
			if(vec[i]>=48 && vec[i]<=57){
					tmp.push_back(vec[i]-48);
				}else{
					cerr << "Invalid Input";
					return;
					break;
				}
		}
		this->size=tmp.size();
	}
	BigInt(char* vec, int size){
			this->charArray=vec;

			vector<int>& tmp =this->intVec;
					tmp.reserve(this->size);
					int k=0;
					if(vec[0]==43 || vec[0]==45){
						if(vec[0]==45){
							if(vec[1]>=48 && vec[1]<=57){
								int x=vec[1];
								x=x-48;
								tmp.push_back(x*(-1));
								k=2;
							}else{
								cerr << "Invalid Input";
								return;
							}

						}else{
						k=1;}
					}

					for(int i=k;i<size;i++)
							{
						if(vec[i]>=48 && vec[i]<=57){
								tmp.push_back(vec[i]-48);
							}else{
								cerr << "Invalid Input";
								return;
								break;
							}
					}
					this->size=tmp.size();
		}
	BigInt operator+(BigInt& val);
	vector<int> addTwoNum(BigInt& val);
	BigInt operator-(BigInt& val);
	vector<int> subtractTwoNum(BigInt& val);
	BigInt operator*(BigInt& val);
	vector<int> multiplyTwoNum(BigInt& val);
	bool operator!();
	bool operator==(BigInt& val);
	bool operator>=(BigInt& val);
	bool operator>(BigInt& val);
	bool operator<=(BigInt& val);
	bool operator<(BigInt& val);
	BigInt operator++();
	BigInt operator++(int val);
	BigInt operator--();
	BigInt operator--(int val);
	friend ostream& operator<<( ostream& out, BigInt& num);
	friend istream& operator>>( istream& cin, BigInt& num);

	~BigInt(){
		//delete[] this->charArray;
	}

};




#endif /* HW8_H_ */
