

void test();

int sum(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9);


int main() {

	
	sum(1,2,3,4,5,6,7,8,0);

}

void test(){
	int x = 11;
}

int sum(int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8, int v9){
	test();
	int result = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + v9;
	return result;

}
