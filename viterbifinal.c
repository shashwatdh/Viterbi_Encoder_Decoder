#include<stdio.h>
struct state
{
	int value;
	int d[2];
	int e[2];
	int val1;
	int val2;
	int decode;
	int state;
};

int main()
{
	struct state s[4];
	int i,j,k=0;
	for(i=0;i<4;i++)
	{
		s[i].value=0;
		s[i].val1=0;
		s[i].val2=0;
		
	}
	//state1
	s[0].d[0]=0;
	s[0].d[1]=0;
	
	s[0].e[0]=1;
	s[0].e[1]=1;
	
	s[0].decode=0;
	//state2
	s[1].d[0]=0;
	s[1].d[1]=1;
	
	s[1].e[0]=1;
	s[1].e[1]=0;
	
	s[1].decode=0;
	//state3
	s[2].d[0]=1;
	s[2].d[1]=1;
	
	s[2].e[0]=0;
	s[2].e[1]=0;
	
	s[2].decode=1;
	//state4
	s[3].d[0]=1;
	s[3].d[1]=0;
	
	s[3].e[0]=0;
	s[3].e[1]=1;
	
	s[3].decode=1;
	
	/*int no_enc;
	printf("\n enter no. of encoded bits:");
	scanf("%d",&no_enc);
	int r=no_enc/2;
	int enc[no_enc];
	printf("\n enter encoded bits:");
	for(i=0;i<no_enc;i++)
	{
		printf("\nbit-%d:",i);
		scanf("%d",&enc[i]);
	}*/
	
	int istate[2]={0,0},output[2];
	int buf,z=0;
	int cnt=0,l,n;
	int no_enc;
	int r;
	int ch;
	int bitpos,pos;
	
	printf("\n------------------sender side----------------");
	printf("\n enter size of data:");
	scanf("%d",&n);
	r=n;
	no_enc=2*n;
	int data[n];
	int enc[no_enc];
	printf("\n enter data bits!!");
	for(j=0;j<n;j++)
	{
	 printf("\n enter data bit-%d:",j+1);
	 scanf("%d",&data[j]);	
	}
	  
	for(l=0;l<n;l++)
	{
		printf("\n initial state:");
		for(i=0;i<2;i++)
		  printf("%d",istate[i]);
		  output[0]=(data[l]+istate[1])%2;
		  buf=(data[l]+istate[0])%2;
		  output[1]=(buf+istate[1])%2;
			istate[1]=istate[0];
			istate[0]=data[l];
			enc[z]=output[0];
			z++;
			enc[z]=output[1];
			z++;
		printf("\n state changed to:");
		for(i=0;i<2;i++)
		  printf("%d",istate[i]);
		  
		printf("\n output corresponding to bit-%d:",k+1);
		for(i=0;i<2;i++)
		  printf("%d",output[i]);
		  printf("\n");
	}
	
	printf("\n encoded numbers are:");
	for(l=0;l<no_enc;l++)
	    printf("%d",enc[l]);
	
	printf("\ndo you want to make changes in encoded bits to be sent ?(1-yes,0-no)");
	scanf("%d",&ch);  
	if(ch==1)
	{
		printf("\n enter position where error has to be introduced:");
		scanf("%d",&bitpos);
		pos=bitpos-1;
		printf("\n present value at position-%d is %d",bitpos,enc[pos]);
		enc[pos]=(enc[pos]==0)?1:0;
		printf("\n value at position-%d has been changed to %d",bitpos,enc[pos]);
		printf("\n editted encoded bits are:");
			for(l=0;l<no_enc;l++)
	             printf("%d",enc[l]);
	}
	
	printf("\nfinal encoded bits to be sent are:");
	for(l=0;l<no_enc;l++)
	             printf("%d",enc[l]);
	   printf("\n");
	   printf("\n---------------------receiver side------------------");
	   printf("\n");
	printf("\n encoded bits are:");
	for(i=0;i<no_enc;i++)
	  printf("%d",enc[i]);
	  
	  printf("\n alternate elements:");
	  for(i=0;i<no_enc;i=i+2)
	  {
	  	printf("\n%d-%d",i,enc[i]);
	  }
	  int x,y,temp0,temp1,temp2,temp3;
	  int hamdist[4][r];
	  int st_trans[4][r];
	  int decode[4][r];
	  int a[2],b[2];
	  int smallest,count=0,position;
	  int dec[r];
	  for(i=0;i<no_enc;i=i+2)
	  {
	  	for(j=0;j<4;j++)
	  	{
	  		a[0]=(enc[i]+s[j].d[0])%2;
	  		a[1]=(enc[i+1]+s[j].d[1])%2;
	  		
	  		b[0]=(enc[i]+s[j].e[0])%2;
	  		b[1]=(enc[i+1]+s[j].e[1])%2;
	  		
	  		x=a[0]+a[1];
	  		y=b[0]+b[1];
	  		
	  		switch(j)
	  		{
	  			case 0:  temp0=s[0].value;
				        s[0].val1=x+s[0].value;
	  			        s[0].val2=y+s[1].value;
	  			        if(s[0].val1<s[0].val2)
	  			          {
	  			          	s[0].value=s[0].val1;
	  			          	st_trans[0][k]=0;
							}
							else
							{
							 s[0].value=s[0].val2;
							 st_trans[0][k]=1;	
							}
							hamdist[0][k]=s[0].value;
							decode[0][k]=0;
							break;
				case 1: temp1=s[1].value;
				        s[1].val1=x+s[2].value;
	  			        s[1].val2=y+s[3].value;
	  			        if(s[1].val1<s[1].val2)
	  			          {
	  			          	s[1].value=s[1].val1;
	  			          	st_trans[1][k]=2;
							}
							else
							{
							 s[1].value=s[1].val2;
							 st_trans[1][k]=3;	
							}
							hamdist[1][k]=s[1].value;
							decode[1][k]=0;
							break;
				case 2: temp2=s[2].value;
				        s[2].val1=x+temp0;
	  			        s[2].val2=y+temp1;
	  			        if(s[2].val1<s[2].val2)
	  			          {
	  			          	s[2].value=s[2].val1;
	  			          	st_trans[2][k]=0;
							}
							else
							{
							 s[2].value=s[2].val2;
							 st_trans[2][k]=1;	
							}
							hamdist[2][k]=s[2].value;
							decode[2][k]=1;
							break;
				case 3: temp3=s[3].value;
				         s[3].val1=x+temp2;
	  			        s[3].val2=y+s[3].value;
	  			        if(s[3].val1<s[3].val2)
	  			          {
	  			          	s[3].value=s[3].val1;
	  			          	st_trans[3][k]=2;
							}
							else
							{
							 s[3].value=s[3].val2;
							 st_trans[3][k]=3;	
							}
							hamdist[3][k]=s[3].value;
							decode[3][k]=1;
							break;
			  }
		  }
		  k++;
	  }
	  printf("\nno. of columns-%d",k);
	  printf("\n hamming dist matrix:\n");
	  for(i=0;i<4;i++)
	  {
	  	for(j=0;j<k;j++)
	  	  printf("%d",hamdist[i][j]);
	  	  printf("\n");
	  }
	   printf("\n state transition matrix:\n");
	  for(i=0;i<4;i++)
	  {
	  	for(j=0;j<k;j++)
	  	  printf("%d",st_trans[i][j]);
	  	  printf("\n");
	  }
	   printf("\n decoder matrix:\n");
	  for(i=0;i<4;i++)
	  {
	  	for(j=0;j<k;j++)
	  	  printf("%d",decode[i][j]);
	  	  printf("\n");
	  }
	 printf("\n last column of hamdist matrix:");   // optional for testing purpose
	  for(i=0;i<4;i++)
	  {
	     printf("\t%d",hamdist[i][k-1]);
	  }
	   smallest=hamdist[0][k-1];
	  for(i=0;i<4;i++)
	  {
	     	if(hamdist[i][k-1]<=smallest)
	     	{
	     			smallest=hamdist[i][k-1];
	     	         position=i;
			 }
		
	  }
	  printf("\n smallest value in last column is-%d",smallest);   //optional for testing purpose
	  printf("\n position of smallest value is:%d",position);      //optional for testing purpose
	  for(i=0;i<4;i++)
	  {
	     	if(hamdist[i][k-1]==smallest)
	     	count++;
	  }
	  printf("\nno. of entries having smallest value are-%d",count);   //optional for testing purpose
	  if(count==1)
	  {
	  	printf("\n decoding....");
	  	for(i=k-1;i>=0;i--)
	  	{
	  		dec[i]=decode[position][i];
	  		position=st_trans[position][i];
		  }
	  }
	  else 
	   {
	   	printf("\n encountered ambiguity in last column!!!");
	   		for(i=k-1;i>=0;i--)
	  	{
	  		dec[i]=decode[position][i];
	  		position=st_trans[position][i];
		  }
		} 
	    printf("\n decoded data:");
	  for(i=0;i<k;i++)
	    printf("\t%d",dec[i]);
}
