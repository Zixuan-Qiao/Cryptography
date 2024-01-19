#include<stdio.h>
#include<stdlib.h>
void ExtendedEuclidean(int a,int b);
int Montgomery(int b,int e,int n);
void EN();
void DE();
char ea[100];
int ba[100];
int temp[3];
int m;
int p=127;
int q=163;
int e=53;
int n=p*q;
int phi=(p-1)*(q-1);
int d;
int c;
void main()
{
	printf("选取的p=127,q=163,e=53\n");
	printf("n=20701,phi=20412\n");
	ExtendedEuclidean(e,phi);
	d=temp[1];
	if(d<0) d+=phi;
	printf("解密密钥d为:");
	printf("%d\n",d);
	FILE *fp;
	printf("请在文件中输入要加密的信息，内容为字母。\n");
	fp=fopen("test.txt", "r");	
	printf("以下出现顺序为：文件中的字符 加密后 解密后:\n");
	char word;
	while ((word = fgetc(fp)) != EOF) {
		printf("%c ",word);
		m=word-96;	
		EN();
		printf("%d ",c);
		DE();
		printf("%c\n",m+96);
	}
	fclose(fp);
}

void ExtendedEuclidean(int a,int b)
{
	int x,y;
	int x1,y1;
	int r;
	if(b==0){
		x1=1;
		y1=0;
		x=x1;
		y=y1;
		r=a;
		temp[0]=r;
		temp[1]=x;
		temp[2]=y;
	}
	else{
		ExtendedEuclidean(b,a%b);
		r=temp[0];
		x1=temp[1];
		y1=temp[2];
		x=y1;
		y=x1-a/b*y1;
		temp[0]=r;
		temp[1]=x;
		temp[2]=y;
	}
}

int Montgomery(int b,int e,int n)
{
	for(int i=0;i<100;i++){
		ea[i]=0;
		ba[i]=0;
	}
	int r=0;
	int b1,b2;
	int a;
	int bacounter=0;
	itoa(e,ea,2);	
	for(i=0;i<100;i++){
		if(ea[i]==0) break;
		r++;
	}
	int t[100];
	for(i=0;i<r;i++){
		t[i]=ea[i];
	}
	for(i=0;i<r;i++){
		ea[i]=t[r-i-1];
	}
	r-=1;
	b1=b;
	ba[bacounter]=b1;
	bacounter++;
	for(i=0;i<r;i++){
		b2=(b1*b1)%n;
		ba[bacounter]=b2;
		bacounter++;
		b1=b2;
	}
	int result=1;
	for(int j=0;j<bacounter;j++){
		a=ba[j];
		if(ea[j]=='0')
			continue;
		result*=a;
		result=result%n;
	}
	result=result%n;
	return result;
}

void EN()
{
	c=Montgomery(m,e,n);
}

void DE()
{
	m=Montgomery(c,d,n);
}
