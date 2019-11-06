#include"BigInt.h"
#include<ostream>

	void insertIntoCarryVector(vector<int>& v, int& temp, int& carry){

		if(temp>9){
			carry=temp/10;
			temp=temp%10;
			v.push_back(temp);
		}else{
			v.push_back(temp);
			carry=0;
		}
	}

	void insertIntoBorrowVector(vector<int>& v, int& temp, int& borrow){

		if(temp<0){
			borrow=1;
			temp=temp + 10;
			v.push_back(temp);
		}else{
			v.push_back(temp);
			borrow=0;
				}
		}

	void vectorReverse(vector<int>& v){
		int size= v.size();
		int i=0, j= size-1;

		while(i<=j){
			//cout << v[j];
			int temp =v[i];
			v[i]=v[j];
			v[j]=temp;
			i++;
			j--;

		}
	}

	vector<int> BigInt::subtractTwoNum(BigInt& val){
			int numSize1=this->size;
			int numSize2=val.size;
			vector<int> v;
			int borrow=0;
			int i=numSize1-1;
			int j=numSize2-1;
			int temp=0;
			bool num1Flag=false;
			bool num2Flag=false;
			bool endFlag=false;
			BigInt n1= *this;
			BigInt n2= val;
			vector<int>& num1=n1.intVec;
			vector<int>& num2=n2.intVec;

			if(num1[0]<0){
				num1[0] *=(-1);
				num1Flag=true;
			}
			if(num2[0]<0){
				num2[0] *=(-1);
				num2Flag=true;
			}
			if(num1Flag && num2Flag){
				if(n2>n1){
					vector<int> tm = num1;
					num1=num2;
					num2=tm;
					endFlag=false;
				}else{
					endFlag=true;
				}
			}else if(num1Flag){
				BigInt vv = (n1 + n2);
				vector<int>& k= vv.intVec;
				k[0] *= (-1);
				return vv.intVec;
			}
			else if(num2Flag){
				BigInt vv = (n1 + n2);
				return vv.intVec;
			}else{
			if(n2 > n1){
				vector<int> tm = num1;
				num1=num2;
				num2=tm;
				endFlag=true;
			}else{
				endFlag=false;
			}}
			while(i>=0||j>=0){
				int numOne= i <0 ? 0 :  num1[i];
				int numTwo= j <0 ? 0 :  num2[j];

				temp= (numOne-borrow)- numTwo;
				insertIntoBorrowVector(v,temp,borrow);
				i--;
				j--;

			}
			if(borrow!=0){
				v.push_back(borrow);
				borrow=0;
			}
			vectorReverse(v);
			if(endFlag){
				v[0] *= (-1);
			}
			return v;
	}
	vector<int> BigInt::addTwoNum(BigInt& val){
				BigInt n1= *this;
				BigInt n2= val;
				int numSize1=this->size;
				int numSize2=val.size;
				vector<int> v;
				int carry=0;
				int i=numSize1-1;
				int j=numSize2-1;
				int temp=0;
				vector<int>& num1=n1.intVec;
				vector<int>& num2=n2.intVec;
				bool num1Flag=false;
				bool num2Flag=false;
				bool endFlag=false;


				if(num1[0]<0){
					num1[0] *=(-1);
					num1Flag=true;
				}
				if(num2[0]<0){
					num2[0] *=(-1);
					num2Flag=true;
				}
				if(num1Flag && num2Flag){
					endFlag=true;
				}else if(num1Flag){
					BigInt vv;
					if(n1>n2){
						vv=n1-n2;
						vv.intVec[0] =vv.intVec[0]*(-1);
						return vv.intVec;
					}
					else{
							vv=n2-n1;
							return vv.intVec;
					}

				}
				else if(num2Flag){
					BigInt vv;
					if(n1>n2){
						vv=n1-n2;
						return vv.intVec;
					}
					else{
							vv=n2-n1;
							vv.intVec[0] =vv.intVec[0]*(-1);
							return vv.intVec;
					}
				}

				while(i>=0||j>=0){

					int numOne= i <0 ? 0 :  num1[i];
					int numTwo= j <0 ? 0 :  num2[j];
					temp= numOne+ numTwo +carry;
					insertIntoCarryVector(v,temp,carry);
					i--;
					j--;

				}
				if(carry!=0){
					v.push_back(carry);
					carry=0;
				}
				vectorReverse(v);
				if(endFlag){
					v[0] *= (-1);
					}
				return v;
	}
	vector<int> BigInt::multiplyTwoNum(BigInt& val){
					BigInt n1= *this;
					BigInt n2= val;
					int numSize1=this->size;
					int numSize2=val.size;
					int carry=0;
					vector<int> final_vec;
					final_vec.push_back(0);
					BigInt finalVal(final_vec);
					vector<int>& num1=n1.intVec;
					vector<int>& num2=n2.intVec;
					bool num1Flag=false;
					bool num2Flag=false;
					bool endFlag=false;
					int zeroes=0;

					if(num1[0]<0){
						num1[0] *=(-1);
						num1Flag=true;
					}
					if(num2[0]<0){
						num2[0] *=(-1);
						num2Flag=true;
					}
					if(num1Flag ^ num2Flag){
						endFlag=true;
					}
					for(int i=numSize2-1;i>=0;i--){
						int numTwo= i <0 ? 0 :  num2[i];
						vector<int> v;
						for(int k=0;k<zeroes;k++){
							v.push_back(0);
						}

						for(int j=numSize1-1;j>=0;j--){
							int numOne= j <0 ? 0 :  num1[j];
							int temp = numOne*numTwo +carry;
							//cout << temp << endl;
							v.push_back(temp%10);
							carry=temp/10;
						}
						if(carry!=0){
							v.push_back(carry);
							carry=0;
						};

						BigInt tmp(v);
						vectorReverse(tmp.intVec);
						finalVal= finalVal + tmp;
						v.clear();
						zeroes++;
					}

					if(endFlag){
						finalVal.intVec[0] *= (-1);
							}
					return finalVal.intVec;
		}
BigInt BigInt::operator+(BigInt& val){
		vector<int> v = addTwoNum(val);
		BigInt b(v);
		return b;

	}

BigInt BigInt::operator-(BigInt& val){

		vector<int> v = subtractTwoNum(val);
		BigInt b(v);
		return b;

	}

BigInt BigInt::operator*(BigInt& val){
		vector<int> v= multiplyTwoNum(val);
		BigInt b(v);
		return b;
	}

bool BigInt::operator!(){
	if(this->size!=0){
		vector<int>& b= this->intVec;
		for(int i=0;i<=b.size();i++){
			if (this->intVec[i]!=0){
				return false;
			}
		}
		return true;
	}
	return false;
}

bool BigInt::operator==(BigInt& val){

		vector<int> num1=this->intVec;
		vector<int> num2=val.intVec;

		bool num1Flag=false;
		bool num2Flag=false;
		bool endFlag=false;
		int zeroes=0;

		if(num1[0]<0){
			num1[0] *=(-1);
			num1Flag=true;
		}
		if(num2[0]<0){
			num2[0] *=(-1);
			num2Flag=true;
		}
		if(num1Flag ^ num2Flag){
			return false;
		}

		if(num1.size()==num2.size()){
			int i=0;
			while(i<num1.size()){
				if(num1[i]!=num2[i]){
					return false;
				}
				i++;
			}
			return true;
		}else{
			return false;
		}
	}

bool BigInt::operator>=(BigInt& val){

		vector<int> num1=this->intVec;
		vector<int> num2=val.intVec;

		bool num1Flag=false;
		bool num2Flag=false;
		bool endFlag=false;
		int zeroes=0;

		if(num1[0]<0){
			num1[0] *=(-1);
			num1Flag=true;
		}
		if(num2[0]<0){
			num2[0] *=(-1);
			num2Flag=true;
		}
		if(num1Flag && num2Flag){
			vector<int> tmp = num1;
			num1=num2;
			num1=tmp;
			endFlag=true;
		}
		else if(num1Flag){
			return false;

		} else if(num2Flag){
			return true;
		}

		if(num1.size()>=num2.size()){
			int i=0;
			while(i<num1.size()){
				if(num1[i]<num2[i]){
					if(endFlag){return true;}
					return false;
				}else if(num1[i]>num2[i]){
					if(endFlag){return false;}
					return true;
				}
				i++;
			}
			return true;
		}else{
			if(endFlag){return true;}
			return false;
		}
	}

bool BigInt::operator>(BigInt& val){

		vector<int> num1=this->intVec;
		vector<int> num2=val.intVec;
		bool num1Flag=false;
				bool num2Flag=false;
				bool endFlag=false;
				int zeroes=0;

				if(num1[0]<0){
					num1[0] *=(-1);
					num1Flag=true;
				}
				if(num2[0]<0){
					num2[0] *=(-1);
					num2Flag=true;
				}
				if(num1Flag && num2Flag){
					vector<int> tmp = num1;
					num1=num2;
					num1=tmp;
					endFlag=true;
				}
				else if(num1Flag){
					return false;

				} else if(num2Flag){
					return true;
				}

		if(num1.size()>=num2.size()){
			int i=0;
			while(i<num1.size()){
				if(num1[i]>num2[i]){
					if(endFlag){return false;}
					return true;
				}else if(num1[i]<num2[i]){
					if(endFlag){return true;}
					return false;
				}
				i++;
			}
			return false;
		}else{
			if(endFlag){return true;}
			return false;
		}
	}


bool BigInt::operator<=(BigInt& val){

		vector<int> num1=this->intVec;
		vector<int> num2=val.intVec;

		bool num1Flag=false;
		bool num2Flag=false;
		bool endFlag=false;
		int zeroes=0;

		if(num1[0]<0){
			num1[0] *=(-1);
			num1Flag=true;
		}
		if(num2[0]<0){
			num2[0] *=(-1);
			num2Flag=true;
		}
		if(num1Flag && num2Flag){
			vector<int> tmp = num1;
			num1=num2;
			num1=tmp;
			endFlag=true;
		}
		else if(num1Flag){
			return true;

		} else if(num2Flag){
			return false;
		}

		if(num2.size()>=num1.size()){
			int i=0;
			while(i<num2.size()){
				if(num2[i]<num1[i]){
					if(endFlag){return true;}
					return false;
				}else if(num2[i]>num1[i]){
					if(endFlag){return true;}
					return true;
				}
				i++;
			}
			return true;
		}else{
//			if(endFlag){return true;}
			return false;
		}
	}

bool BigInt::operator<(BigInt& val){

		vector<int> num1=this->intVec;
		vector<int> num2=val.intVec;
				bool num1Flag=false;
				bool num2Flag=false;
				bool endFlag=false;
				int zeroes=0;

				if(num1[0]<0){
					num1[0] *=(-1);
					num1Flag=true;
				}
				if(num2[0]<0){
					num2[0] *=(-1);
					num2Flag=true;
				}
				if(num1Flag && num2Flag){
					vector<int> tmp = num1;
					num1=num2;
					num1=tmp;
					endFlag=true;
				}
				else if(num1Flag){
					return true;

				} else if(num2Flag){
					return false;
				}
		if(num2.size()>=num1.size()){
			int i=0;
			while(i<num2.size()){
				if(num2[i]>num1[i]){
					if(endFlag){return true;}
					return true;
				}else if(num2[i]<num1[i]){
					if(endFlag){return true;}
					return false;
				}
				i++;
			}
			return false;
		}else{
			if(endFlag){return true;}
			return false;
		}
	}

BigInt BigInt::operator++(){

	BigInt& num1 = *this;
	vector<int> tmp;
	tmp.push_back(1);
	BigInt num2(tmp);
	num1=num1+num2;
	return num1;

}

BigInt BigInt::operator++(int val) {
	//vector<int> num_vec=this->intVec;
	BigInt num = *this;
	BigInt& num1 = *this;
	vector<int> tmp;
	tmp.push_back(1);
	BigInt num2(tmp);
	num1 = num1 + num2;
	return num;

}

BigInt BigInt::operator--(){

	BigInt& num1 = *this;
		vector<int> tmp;
		tmp.push_back(1);
		BigInt num2(tmp);
		num1=num1-num2;
		return num1;
}
BigInt BigInt::operator--(int val){

		BigInt num = *this;
		BigInt& num1 = *this;
		vector<int> tmp;
		tmp.push_back(1);
		BigInt num2(tmp);
		num1 = num1 - num2;
		return num;
}

ostream& operator<<(ostream& out,BigInt& num){
	vector<int>& num1=num.intVec;
	for(int i=0;i<num1.size();i++){
		cout << num1[i];
	}
	return out;
}

istream& operator>>(istream& in, BigInt& num){
		vector<int> vv;
		bool flag=false;
		while(true){
			char c = cin.get();

			//cin >> c;
			if((c>='0' && c<='9' )|| c==45 || c==43){
				if(c!=45 && c!=43){
				vv.push_back(c-48);
				}else{
					if(flag){
						cerr << "Invalid Input";
						exit;
					}else{
					flag=true;}
				}
			}else{
				if(c=='\n'){
					break;
				}else{
					cerr << "Invalid Input";
					exit;
				}
			}
		}
		if(flag){
			vv[0] *=(-1);
		}
		BigInt obj(vv);
		num=obj;
		return in;

}

