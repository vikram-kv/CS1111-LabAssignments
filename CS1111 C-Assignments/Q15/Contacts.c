//Necessary header files are included
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Global Variables
long int count=0;//A static global variable to keep track of number of contacts in heap
const char* NOTAVAILABLE="NA";//A global constant string which is "NA"


//An enumeration for indicating success /failure of a function operation.
enum result{SUCCESS=+1,FAILURE=-1};

//Definition of a enumerated type as a set of integer constants
//which correspond to maximum length that can stored in fields of
//the contact data type.
enum max_length{
SN=30,//SN-Max size of name field
SO=50,//SO-Max Size of organization field
SM=15,//SM-Max Size of number field in mobile data type
SH=120,//SH-Max Size of home address field
SP=10,//SP-Max Size of pincode field
SS=25//SS-Max Size of state field
};

//Definition of a set of integer constants which will be used later in the program for seeking user choices
//The integer constants have their values starting from 1.
enum choice
{
    NAME=1,
    ORGANISATION,
    MOBILE,
    HOME,
    PINCODE,
    STATE
};

//A datatype which is used for creating a linked list of mobile numbers
//It contains a mobile number called number and a pointer to its own type called mnext.
struct mobile
{
    char number[SM];
    struct mobile* mnext;
};

//The datatype contact is defined.
//The fields inside it are strings like name,organisation, home,pincode and pincode.
//It also contains a pointer to the head of the linked list of the mobile numbers of the contact which is mptr
//It also contains a pointer to its own type for connection in linked list
struct contact
{
    char name[SN];
    char organisation[SO];
    struct mobile* mptr;
    char home[SH];
    char pincode[SP];
    char state[SS];
    struct contact* next;
};

//A datatype which will only be used for sorting purposes which HOLDS-A contact by having the address of a contact
//It will be used for storing the addresses of the contacts whose names have the same beginning letters
//It also has a pointer to its own type as a linked list of this type will be created
struct contactptr
{
	struct contact* ptr;
	struct contactptr* next;
};

//Function Prototypes:

void fgetline(char*,int,FILE*,char);
void Initialize(struct contact*);
void Dealloc_Memory(struct contact*);
void Dealloc_List(struct contact*);
void Contact_Copy(struct contact*,const struct contact*);
void Swap_Items(struct contact*,struct contact*);
void Sort_List(struct contact*,enum choice);
void Dealloc_Cpointer(struct contactptr*);
void Sort_Begin_Letter(struct contactptr*);
void Print_Node(struct contact*);
void Print_List(struct contact*);
void Print_Mobile(FILE*,struct mobile*);
void Mobile_Operations(struct contact*);
void Print_SubList(struct contact*,enum choice,const char*);
int Write_List(struct contact*,const char*);
int Menu();
int User_Interface();
struct mobile* Search_Mobile(struct contact*,const char*);
long Calc_Size(struct contact*);
char* Find_Small_Mobile(struct contact* ptr);
struct contact* Alloc_Memory();
struct contact* Create_List(const char*);
struct contact* Min_Value(struct contact*,enum choice);
struct contact* Pointer_To_Pos(struct contact*,long);
struct contact* Insert_Into(struct contact*,long);
struct contact* Delete_Node(struct contact*,enum choice,char[]);
struct contact* Find_Contact(struct contact*,struct contact);
struct contact* Update_Single_Contact(struct contact*);
struct contactptr* Create_List_Of_Pointers_Begin(struct contact*,const char);
struct contactptr* CMinvalue_By_Name(struct contactptr*);
struct mobile* Delete_Mobile(struct contact* ptr,const char* match);
//Main Function
int main()
{
    return User_Interface();//The Return value of User_Interface() is returned by the main() function to the terminal
}

//Function to dynamically allocate memory for a single object of contact and return a pointer to it.
struct contact* Alloc_Memory()
{
    struct contact* temp_ptr=(struct contact*)malloc(sizeof(struct contact));
    count++;//number of contacts in heap memory is raised by 1.
    return temp_ptr;//Address of the newly created node is returned
}

//A function which is used for reading a string that can store at max 'size' number of characters(including '\0') from FP's buffer till the character
//letter is read.The character letter is not stored.
void fgetline(char* string,int size,FILE* FP,char letter)
{
    int read;//variable used for storing the ascii value of character read from FP's buffer
    int index=0;//index is the index of the string array at which the read character must be stored.
    while(index<size-1)//loop to iteratively read characters from FP's buffer
    {
        read=fgetc(FP);
        if(read==letter||read==EOF)
            break;
        string[index]=read;
        index++;
    }
    string[index]='\0';//insertion of null terminator
    return;
}

//Function to initialize the newly allocated memory for a contact whose address is ptr with legal values.
void Initialize(struct contact* ptr)
{
    strcpy(ptr->name,NOTAVAILABLE);
    strcpy(ptr->organisation,NOTAVAILABLE);
    ptr->mptr=NULL;
    strcpy(ptr->home,NOTAVAILABLE);
    strcpy(ptr->pincode,NOTAVAILABLE);
    strcpy(ptr->state,NOTAVAILABLE);
    ptr->next=NULL;
    return;
}

//Function to free memory of a linked list of mobiles.The address of the first node in the list is ptr
void Dealloc_Mobile(struct mobile* ptr)
{
    struct mobile* temp;
    while(ptr!=NULL)//Loop to free the memory allocated node by node till the last node
    {
        temp=ptr;
        ptr=ptr->mnext;
        free(temp);
    }
}

//Function to deallocate the memory allocated to a contact whose address is ptr
void Dealloc_Memory(struct contact* ptr)
{
    Dealloc_Mobile(ptr->mptr);//The memory allocated for storing the contact's mobile numbers is freed.
    free(ptr);//the memory allocated to contact is freed.
    count--;//The total number of contacts in memory is decreased by 1.
    return;
}

//Function to deallocate memory of an entire linked list of contacts whose head's address is passed as an argument
void Dealloc_List(struct contact* head)
{
    struct contact* temp= NULL;
    while(head!=NULL)//Loop to iteratively free the memory allocated to each contact in the list
    {
        temp=head;
        head=head->next;
        Dealloc_Memory(temp);
    }
    return;
}

//Function to open a file, read its content, dynamically allocate storage, link the allocated storage
//and return a pointer to its head.
struct contact* Create_List(const char * filename)
{
    FILE* filepointer=fopen(filename,"r");//filename is opened in read mode
    struct contact* head=NULL;//head is a pointer to the first node in the linked list
    struct contact* tail=NULL;//last is a pointer to the last node in the linked list
    struct contact* newcontact=NULL;//newcontact is a pointer to a newly created contact
    if(filepointer==NULL)//detection of ERROR opening file
    {
        printf("\nERROR: Failed to open the file/File doesn't exist.");
        return head;
    }
    else
    {
        fseek(filepointer,0,SEEK_END);//moving the file pointer to the end of the file
        long int size=ftell(filepointer);//determining the size of the file
        fseek(filepointer,0,SEEK_SET);//bringing the file pointer to the beginning of the file
        while((ftell(filepointer))<size)//while filepointer is not at end of the file
        {
            newcontact=Alloc_Memory();//memory for newcontact is allocated
            if(newcontact==NULL)//Checking for failure to allocate memory
            {
                printf("\nERROR: Failed to allocate more memory from heap.\nProgram will remain operational up to what has been loaded into the heap.");
                return head;
            }
            else
            {
                char tempmobile[SM];//tempmobile is a string which is used for reading and storing mobile numbers temporarily
                struct mobile *mhead=NULL,*mtail=NULL,*newmobile=NULL;//mhead,mtail and newmobile are the pointers to first,last and a newly created mobile of the linked list of mobiles
                Initialize(newcontact);//newcontact is initialized
                fgetline(newcontact->name,SN,filepointer,'\t');//name is read
                fgetline(newcontact->organisation,SO,filepointer,'\t');//organisation is read
                fgetline(tempmobile,SM,filepointer,'\t');//first mobile is read
                while(strcmp(tempmobile,"END")!=0)//while the mobile number is not END
                {
                    newmobile=(struct mobile*)(malloc(sizeof(struct mobile)));//a new mobile is created
                    if(newmobile==NULL)//Failure to allocate memory for storing a new mobile at newmobile
                    {
                        break;
                    }
                    newmobile->mnext=NULL;//initialization of mnext
                    strcpy(newmobile->number,tempmobile);//storing the read tempmobile at newmobile's number
                    if(mhead==NULL)//if the list of mobile numbers is empty
                    {
                        mhead=mtail=newmobile;
                    }
                    else
                    {//Linking of the newmobile with the tail
                        mtail->mnext=newmobile;
                        mtail=newmobile;
                    }
                    fgetline(tempmobile,SM,filepointer,'\t');//the next mobile number is read
                }
                newcontact->mptr=mhead;//the address of head of the linked list of mobiles is stored in mptr at newcontact
                fgetline(newcontact->home,SH,filepointer,'\t');//home is read
                fgetline(newcontact->pincode,SP,filepointer,'\t');//pincode is read
                fgetline(newcontact->state,SS,filepointer,'\n');//state is read
                newcontact->next=NULL;
                if(head==NULL)//if list of contacts is empty
                {
                    head=tail=newcontact;
                }
                else
                {//linking the newcontact at the tail of the existing list
                    tail->next=newcontact;
                    tail=newcontact;
                }
            }
        }
    }
    fclose(filepointer);//The file filename is closed
    return head;
}

//Function to print a linked list of mobile numbers into fp's buffer
//The address of the first node in that list is mhead
void Print_Mobile(FILE* fp, struct mobile* mhead)
{
    fprintf(fp,"Mobile(s):");
    while((mhead->mnext)!=NULL)//Loop to print all mobile numbers
    {
        fprintf(fp,"%s,",mhead->number);
        mhead=mhead->mnext;
    }
    fprintf(fp,"%s.\n",mhead->number);
}

//Function to open a file in write mode (Existing content is truncated to zero length)
//and print the fields of the objects of the type contact stored in a linked list whose head
//is passed as a parameter.
int Write_List(struct contact* head,const char* filename)
{
    FILE* filepointer=fopen(filename,"w");//filename is opened in write mode
    if(filepointer==NULL){//detection of ERROR opening file
        printf("\nERROR: Failed to open file/File doesn't exist.");
        return FAILURE;
    }
    else{
        while(head!=NULL)//Loop to iteratively print all the contents of the linked list of contacts whose head is head
        {
            fprintf(filepointer,"NAME:%s\nORGANISATION:%s\n",head->name,head->organisation);
            Print_Mobile(filepointer,head->mptr);
            fprintf(filepointer,"HOME:%s\nPIN CODE:%s\nSTATE:%s\n\n",head->home,head->pincode,head->state);
            head=head->next;
        }
        fclose(filepointer);//filename is closed
        printf("\nSuccessfully written into %s",filename);//Signal to the user indicating successful save operation
        return SUCCESS;
    }
}

//Function to return the address of the smallest mobile number in the list of mobile numbers of the contact whose address is ptr
char* Find_Small_Mobile(struct contact* ptr)
{
    struct mobile *mhead=ptr->mptr,*temp=NULL,*minptr;//mhead is the address of the first mobile in ptr's list of mobile numbers.temp is used to store the address of mobile number in the linked list
    //of mobile numbers.minptr stores the address of the smallest mobile number in the list
    temp=minptr=mhead;//assuming that the mobile number at mhead is smallest
    while(temp!=NULL)//loop to find minptr by comparing it will all numbers in the list
    {
        if(strcmp(temp->number,minptr->number)<0)
            minptr=temp;
        temp=temp->mnext;
    }
    return (minptr->number);//the address of the smallest mobile number is returned
}

//Function which returns a pointer to the contact that has the "minimum" value of a chosen field in a linked list of contacts.The chosen field is determined from the
//integer constant _choice passed to it.begin is the address of the first contact in the list.It is assumed that begin is not null, which will always be ensured in this function call.
struct contact* Min_Value(struct contact* begin,enum choice _choice)
{
    struct contact* tempptr=begin->next;//tempptr will be used for traversal across the list.It is initialized with the address of the second node in the list
    struct contact* Minptr=begin;//minptr is the pointer to the contact which has the minimum value for a certain field
    switch(_choice)
    {
        case 1://field is name
            while(tempptr!=NULL)//Loop for traversal
            {
                if(strcmp(tempptr->name,Minptr->name)<0)//minptr is assigned tempptr if the contact at tempptr has a name which occurs earlier in the dictionary order than the one at Minptr
                {
                    Minptr=tempptr;
                }
                tempptr=tempptr->next;
            }
            break;
        case 2://Same Logic as above with field as organisation
            while(tempptr!=NULL)
            {
                if(strcmp(tempptr->organisation,Minptr->organisation)<0)
                {
                    Minptr=tempptr;
                }
                tempptr=tempptr->next;
            }
            break;
        case 3://Same Logic as above with the field as the number which occurs earliest when arranged in dictionary order (same as increasing order if all numbers have same number of digits)in the mobile number list
            while(tempptr!=NULL)
            {
                if(strcmp(Find_Small_Mobile(tempptr),Find_Small_Mobile(Minptr))<0)
                {
                    Minptr=tempptr;
                }
                tempptr=tempptr->next;
            }
            break;
        case 4://Same logic with field as home
            while(tempptr!=NULL)
            {
                if(strcmp(tempptr->home,Minptr->home)<0)
                {
                    Minptr=tempptr;
                }
                tempptr=tempptr->next;
            }
            break;
        case 5://Same Logic with field as pincode
            while(tempptr!=NULL)
            {
                if(strcmp(tempptr->pincode,Minptr->pincode)<0)
                {
                    Minptr=tempptr;
                }
                tempptr=tempptr->next;
            }
            break;
        case 6://Same logic with field as state
            while(tempptr!=NULL)
            {
                if(strcmp(tempptr->state,Minptr->state)<0)
                {
                    Minptr=tempptr;
                }
                tempptr=tempptr->next;
            }
            break;
        default:
            break;
    }
    return Minptr;//The address of the contact with the "least" field value is returned
}

//Function which copies the contents of ptr2's contact to ptr1's contact
void Contact_Copy(struct contact* ptr1, const struct contact* ptr2)
{
    //ALL field values are copied except for next in order to preserve the links of the linked list
    strcpy(ptr1->name,ptr2->name);
    strcpy(ptr1->organisation,ptr2->organisation);
    (ptr1->mptr)=(ptr2->mptr);
    strcpy(ptr1->home,ptr2->home);
    strcpy(ptr1->pincode,ptr2->pincode);
    strcpy(ptr1->state,ptr2->state);
}

//Function to swap the contents at ptr1 and at ptr2
//Their nexts are not swapped
void Swap_Items(struct contact* ptr1,struct contact* ptr2)
{
    struct contact tempcontact;//a temporary contact to be the third variable for the swap
    struct contact* tempptr=&tempcontact;//a temporary pointer to the temporary contact
    //statements to perform the swap
    Contact_Copy(tempptr,ptr1);
    Contact_Copy(ptr1,ptr2);
    Contact_Copy(ptr2,tempptr);
    return;
}

//Implements Selection Sort on the linked list of contacts where the first node's address is head and _choice is the interger constant
//which represents the field based on which the sort has to be done
void Sort_List(struct contact* head,enum choice _choice)
{
    struct contact* current_ptr=head;//Loop variable for list traversal
    struct contact* minptr=NULL;
    //LOOP INVARIANT:at the end of the ith iteration the first i contacts are sorted
    while((current_ptr->next)!=NULL)//while the current node is not the last node
    {
        minptr=Min_Value(current_ptr,_choice);
        Swap_Items(current_ptr,minptr);//swapping the current contact with the minimum in the list beginning with current contact
        current_ptr=current_ptr->next;
    }
    return;
}

//Function which computes the size of the linked list of contacts whose head is head
//It returns the size.
long Calc_Size(struct contact* head)
{
	struct contact*  temp=head;//Pointer used for traversal
	long size=0;//variable for counting the number of contacts in the list
	while(temp!=NULL)//Loop for traversal
	{
		size++;
		temp=temp->next;
	}
	return size;//number of contacts is returned
}

//Function to return a pointer to a contact whose position in the list is position
//head is the address of the first node in the list
struct contact* Pointer_To_Pos(struct contact* head,long position)
{
	long pos=1;//pos is for keeping track of the current position in the list
	struct contact* temp=head;//variable for traversal
	if(position>Calc_Size(head))//There is no contact at that position
	{
		return NULL;
	}
	while(pos<position)//Loop for list traversal till the positionth node is reached
	{
		pos++;
		temp=temp->next;
	}
	return temp;//Address of the required node is returned
}

//Function for inserting a new contact given by the user at the position "position"in the linked list.
//address of the first element in the list is head
//It returns the address of the first node of the altered linked list
struct contact* Insert_Into(struct contact* head,long position)
{
	long size=Calc_Size(head);//size of the list is found
	struct contact* newcontact=NULL;//newcontact is a pointer to a newly created contact
	struct contact* temp1=NULL;//temp1 and temp2 will be used for adding the node at the appropriate position in the list
	struct contact* temp2=NULL;
	newcontact=Alloc_Memory();//new contact is created
	if(newcontact==NULL)//Detection of failure to allocate memory
	{
		printf("\nERROR: Failed to create memory.");
		return head;
	}
	Initialize(newcontact);//The new contact is initialized
	char tempmobile[SM];//tempmobile is used for temporarily storing the mobile number entered by the user
	struct mobile *mhead=NULL,*newmobile,*mtail;//mhead, mtail and newmobile are pointers to the first, last and a newly created node of the linked list of mobiles of the new contact
	printf("\n \tEnter the name(max %d):",SN);//name is obtained
	fgetline(newcontact->name,SN,stdin,'\n');
	printf("\n \tEnter the organisation(max %d):",SO);//organisation is obtained
	fgetline(newcontact->organisation,SO,stdin,'\n');
	printf("\n \tEnter the mobile numbers line by line (To end,Type END):");//the first mobile number is obtained
	fgetline(tempmobile,SM,stdin,'\n');
	while(strcmp(tempmobile,"END")!=0)//loop to iteratively obtain mobile numbers and add them to the linked list of mobiles
    {
        newmobile=(struct mobile*)(malloc(sizeof(struct mobile)));//memory for a new mobile node is allocated
        if(newmobile==NULL)//Detection of failure to allocate memory
        {
            break;
        }
        newmobile->mnext=NULL;
        strcpy(newmobile->number,tempmobile);//the value of newmobile's number is assigned
        if(mhead==NULL)//if the list of mobile numbers is empty
        {
            mhead=mtail=newmobile;
        }
        else
        {//the new mobile number is inserted in the tail end.
            mtail->mnext=newmobile;
            mtail=newmobile;
        }
        printf("\t");
        fgetline(tempmobile,SM,stdin,'\n');//the next mobile number is obtained.If an "END" is typed, loop is broken
    }
    newcontact->mptr=mhead;//newcontact now has the address of the first mobile in its list of mobile numbers
	printf("\n \tEnter the home address (max %d):",SH);//home address is obtained
	fgetline(newcontact->home,SH,stdin,'\n');
	printf("\n \tEnter the pin code(max %d):",SP);//pin code is obtained
	fgetline(newcontact->pincode,SP,stdin,'\n');
	printf("\n \tEnter the state (max %d):",SS);//state is obtained
	fgetline(newcontact->state,SS,stdin,'\n');
	if(size==0)//if there are no nodes in the list
    {
        return newcontact;
    }
	if(position>size)//is position is grater than size, it is inserted in the tail end of the list
	{
		temp1=Pointer_To_Pos(head,size);//temp1 stores the address of the last node
		temp1->next=newcontact;//new contact is now the new tail
		newcontact->next=NULL;
	}
	else if(position==1)//newcontact must be made the first node
	{
		newcontact->next=head;
		head=newcontact;//newcontact is the first node
	}
	else
	{
		temp1=Pointer_To_Pos(head,position-1);//temp1 will be the pointer to the position below which new contact must be inserted
		temp2=temp1->next;//temp2 stores the address of the node which is the positionth node in the old list
		temp1->next=newcontact;//newcontact is inserted
		newcontact->next=temp2;
	}
	return head;//head of the new linked list of contacts is returned
}

//Function which creates a linked list of contactptrs which store the addresses of the nodes of the linked list whose first node is at head
//and the nodes' name begin with the same letter
//It returns the head of the list of contactpts created by it.
struct contactptr* Create_List_Of_Pointers_Begin(struct contact* head,const char letter)
{
	struct contactptr* chead=NULL;//pointer to the first node
	struct contactptr* ctail=NULL;//pointer to the last node
	struct contactptr* newc=NULL;//newc is a pointer to the newly created node
	while(head!=NULL)//Loop for traversing across the entire linked list
	{
		if(*(head->name)==letter)//if the current node's name begins with letter
		{
			newc=(struct contactptr*)(malloc(sizeof(struct contactptr)));//a new contactptr node is created
			if(newc==NULL)//detection of error allocating memory
			{
				printf("\nERROR: Failed to allocate memory.Only the objects for which pointers were dynamically allocated will be sorted.");
				return chead;
			}
			else
			{
			    //newc is initialized and attached to the appropriate position in the list of ocntactptrs
				newc->next=NULL;
				newc->ptr=head;
				if(chead==NULL)
				{
					chead=ctail=newc;
				}
				else
				{
					ctail->next=newc;
					ctail=newc;
				}
			}
		}
		head=head->next;//loop update statement
	}
	return chead;//the head of the list of contactptrs is returned
}

//Function to return the contactptr whose contact has the the name that occurs first in dictionary order when all the contacts in the linked list of contactptrs are
//whose head is cbegin are considered(as they begin with a certain letter)
struct contactptr* CMinvalue_By_Name(struct contactptr* cbegin)
{
    struct contactptr* ctemp=cbegin->next;//ctemp is the pointer to the second node
    struct contactptr* cminptr=cbegin;//the pointer to the location whose ptr points to a contact which has the name which occurs earliest in dictionary order in the list of contactptrs beginning with cbegin
    while(ctemp!=NULL)//loop for traversing across the entire list of contactptrs
    {
        if(strcmp((ctemp->ptr)->name,(cminptr->ptr)->name)<0)//if ctemp's contact has a name that occurs earlier in dictionary order as compared with that of cminptr
            cminptr=ctemp;
        ctemp=ctemp->next;
    }
    return cminptr;//cminptr is returned
}

//Function for sorting the contacts which begin with a certain letters and whose addresses are stored in a linked list of contactptrs whose head is chead
void Sort_Begin_Letter(struct contactptr* chead)
{
	struct contactptr* temp=chead;//Variable for traversing across the whole list
	struct contactptr* cminptr=NULL;
	while((temp->next)!=NULL)//Loop for traversal
    {
        cminptr=CMinvalue_By_Name(temp);//The contact with the "minimum name" is found
        Swap_Items(temp->ptr,cminptr->ptr);//The contact at the address inside the current node(*temp) is swapped with the contact with the "minimum" name
        temp=temp->next;
    }
}

//The list of contactptrs are deallocated from the memory by calling this function after sorting the contacts whose names begin with a certain letter is done
void Dealloc_Cpointer(struct contactptr* chead)
{
    struct contactptr* temp=NULL;
    while(chead!=NULL){
        temp=chead;
        chead=chead->next;
        free(temp);
    }
}

//Function to print the contents of the contact at ptr onto the screen
void Print_Node(struct contact* ptr)
{
    fprintf(stdout,"\nName:%s\nOrganisation:%s\n",ptr->name,ptr->organisation);//name and organization is printed
    Print_Mobile(stdout,ptr->mptr);//list of mobile numbers is printed
    fprintf(stdout,"Home:%s\nPincode:%s\nState:%s\n",ptr->home,ptr->pincode,ptr->state);//home,state and pincode is printed
    return;
}

//Function to search for a certain mobile number in the list of mobile numbers at ptr.
//The function returns the address of that mobile number(match) if it is found.
//Else it returns NULL
struct mobile* Search_Mobile(struct contact* ptr,const char* match)
{
    struct mobile* found=NULL;
    struct mobile* mtempptr=ptr->mptr;//mtempptr points to the first mobile number in the list of mobiles of ptr
    while(mtempptr!=NULL)//Loop for traversing across the entire list of mobile numbers of ptr.
    {
        if(strcmp(mtempptr->number,match)==0)//if match is found in the list at mtempptr
        {
            found=mtempptr;
            break;
        }
        mtempptr=mtempptr->mnext;
    }
    return found;//address of match in ptr's list of mobiles is returned
}

//Function to print a sublist of contacts where a certain field, based upon a choice _choice, is match.
//The address of the first node in the list of contacts is head
void Print_SubList(struct contact* head,enum choice _choice,const char* match)
{
    switch(_choice)
    {
        case 1://name is the field
            while(head!=NULL)//Loop for traversing across the entire list
            {
                if(strcmp(head->name,match)==0)//if match is the name at head
                {
                    Print_Node(head);
                }
                head=head->next;//Loop update statement
            }
            break;
        case 2://organisation is the field
            while(head!=NULL)//Loop for traversing across the entire list
            {
                if(strcmp(head->organisation,match)==0)
                {
                    Print_Node(head);
                }
                head=head->next;//Loop update statement
            }
            break;
        case 3://mobile number list is chosen
            while(head!=NULL)//Loop for traversing across the entire list
            {
                if(Search_Mobile(head,match)!=0)//if match is found in the list of mobile numbers
                {
                    Print_Node(head);
                }
                head=head->next;//Loop update statement
            }
            break;
        case 4://home address is the field
            while(head!=NULL)//Loop for traversing across the entire list
            {
                if(strcmp(head->home,match)==0)
                {
                    Print_Node(head);
                }
                head=head->next;//Loop update statement
            }
            break;
        case 5://pincode is the field
            while(head!=NULL)//Loop for traversing across the entire list
            {
                if(strcmp(head->pincode,match)==0)
                {
                    Print_Node(head);
                }
                head=head->next;//Loop update statement
            }
            break;
        case 6://state is the field
            while(head!=NULL)//Loop for traversing across the entire list
            {
                if(strcmp(head->state,match)==0)
                {
                    Print_Node(head);
                }
                head=head->next;//Loop update statement
            }
            break;
        default:
            break;
    }
    return;
}

//Function to delete all contacts from a linked list of contacts
//it returns the new head of the linked list of contacts
//It takes in an integer constant called _choice for determining against which field str must be matched
//The address of the first node in the linked list of contacts is head
struct contact* Delete_Node(struct contact* head,enum choice _choice,char str[])
{
    struct contact* temp=head;//variable for traversal across the list
    struct contact* temp2=NULL;//variable which will be used for linking the rest of the list when temp is deleted
    int position=1;//variable indicating the position of the node to be deleted
    int i_count=count;//Initial number of contacts
    switch(_choice)
    {
        case 1://name is the field
            while(temp!=NULL)//loop for traversal
            {
                if(strcmp(temp->name,str)==0){//if name of the current node matches with str
                    if(temp==head)//if temp is the first node in the list
                    {
                        head=temp->next;//head is the next node
                        Dealloc_Memory(temp);//memory for the first node is deallocated
                        temp=head;//loop update
                        position=1;//position is 1
                    }
                    else{
                        temp2=Pointer_To_Pos(head,position-1);//the node preceding the node to be deleted
                        temp2->next=temp->next;//removing temp from the list
                        Dealloc_Memory(temp);//deallocating the memory for temp
                        temp=temp2->next;//loop update
                    }
                }
                else{
                    position++;//position is incremented
                    temp=temp->next;//loop update
                }
            }
            break;
        case 2://organisation is the field
            while(temp!=NULL)//loop for traversal
            {
                if(strcmp(temp->organisation,str)==0){
                    if(temp==head)
                    {
                        head=temp->next;//head is the next node
                        Dealloc_Memory(temp);//memory for the first node is deallocated
                        temp=head;//loop update
                        position=1;//position is 1
                    }
                    else{
                        temp2=Pointer_To_Pos(head,position-1);//the node preceding the node to be deleted
                        temp2->next=temp->next;//removing temp from the list
                        Dealloc_Memory(temp);//deallocating the memory for temp
                        temp=temp2->next;//loop update
                    }
                }
                else{
                    position++;//position is incremented
                    temp=temp->next;//loop update
                }
            }
            break;
        case 3://list of mobile numbers is the choice
            while(temp!=NULL)//loop for traversal
            {
                if(Search_Mobile(temp,str)!=0){
                    if(temp==head)
                    {
                        head=temp->next;//head is the next node
                        Dealloc_Memory(temp);//memory for the first node is deallocated
                        temp=head;//loop update
                        position=1;//position is 1
                    }
                    else{
                        temp2=Pointer_To_Pos(head,position-1);//the node preceding the node to be deleted
                        temp2->next=temp->next;//removing temp from the list
                        Dealloc_Memory(temp);//deallocating the memory for temp
                        temp=temp2->next;//loop update
                    }
                }
                else{
                    position++;//position is incremented
                    temp=temp->next;//loop update
                }
            }
            break;
        case 4://home address is the field
            while(temp!=NULL)//loop for traversal
            {
                if(strcmp(temp->home,str)==0){
                    if(temp==head)
                    {
                        head=temp->next;//head is the next node
                        Dealloc_Memory(temp);//memory for the first node is deallocated
                        temp=head;//loop update
                        position=1;//position is 1
                    }
                    else{
                        temp2=Pointer_To_Pos(head,position-1);//the node preceding the node to be deleted
                        temp2->next=temp->next;//removing temp from the list
                        Dealloc_Memory(temp);//deallocating the memory for temp
                        temp=temp2->next;//loop update
                    }
                }
                else{
                    position++;//position is incremented
                    temp=temp->next;//loop update
                }
            }
            break;
        case 5://pincode is the field
            while(temp!=NULL)//loop for traversal
            {
                if(strcmp(temp->pincode,str)==0){
                    if(temp==head)
                    {
                        head=temp->next;//head is the next node
                        Dealloc_Memory(temp);//memory for the first node is deallocated
                        temp=head;//loop update
                        position=1;//position is 1
                    }
                    else{
                        temp2=Pointer_To_Pos(head,position-1);//the node preceding the node to be deleted
                        temp2->next=temp->next;//removing temp from the list
                        Dealloc_Memory(temp);//deallocating the memory for temp
                        temp=temp2->next;//loop update
                    }
                }
                else{
                    position++;//position is incremented
                    temp=temp->next;//loop update
                }
            }
            break;
        case 6://state is the field
           while(temp!=NULL)//loop for traversal
            {
                if(strcmp(temp->state,str)==0){
                    if(temp==head)
                    {
                        head=temp->next;//head is the next node
                        Dealloc_Memory(temp);//memory for the first node is deallocated
                        temp=head;//loop update
                        position=1;//position is 1
                    }
                    else{
                        temp2=Pointer_To_Pos(head,position-1);//the node preceding the node to be deleted
                        temp2->next=temp->next;//removing temp from the list
                        Dealloc_Memory(temp);//deallocating the memory for temp
                        temp=temp2->next;//loop update
                    }
                }
                else{
                    position++;//position is incremented
                    temp=temp->next;//loop update
                }
            }
            break;
        default:
            break;
    }
    if(i_count==count){// if initial count is same as final count
        printf("\nNo Objects have been deleted.");
    }
    else{
        printf("\n%ld Objects have been deleted.\n\n",i_count-count);
    }
    return head;//head of the list after the nodes have been deleted(if any) is returned
}

//Function to print the list of contacts.head stores the address of the first node
void Print_List(struct contact* head)
{
    struct contact* temp=NULL;
    temp=head;
    if(temp==NULL)//if thee are contacts in the list
    {
        printf("\nThe linked list is empty.");
        return ;
    }
    printf("\nThe list is: \n");
    while(temp!=NULL)//Loop for traversal
    {
        Print_Node(temp);//print the contact at temp
        temp=temp->next;//loop update
    }
    printf("\nTotal of %ld objects are in list.\n\n",count);//count is total number of nodes
    return;
}

//Function to find and return the address of a contact(if any) in the list whose first node is at head and its name is same as match's name
//To account for the fact that contacts may have same names, match also has a single mobile number which is also searched for in the list of mobile numbers of such a contact
struct contact* Find_Contact(struct contact* head,struct contact match)
{
    while(head!=NULL)//Loop for traversing the entire list
    {
        if((strcmp(head->name,match.name)==0)&&(Search_Mobile(head,(match.mptr)->number)!=NULL))//if match's name is same as head's name and match's mobile number is found in the list of mobile numbers of head
        {
            return head;
        }
        head=head->next;//loop update
    }
    return NULL;
}

//Function to add a new mobile  number for the contact at ptr.
//The mobile number to be added is num
void Add_New_Number(struct contact* ptr,const char* num)
{
    struct mobile* newmobile=(struct mobile* )(malloc(sizeof(struct mobile)));//newmobile is the pointer to the newly allocated memory of type mobile
    if(newmobile==NULL)//Detection of failure to allocate memory
    {
        printf("\nFailed to add number due to lack of memory.");
        return;
    }
    else
    {
        struct mobile* head=(ptr->mptr);//head stores the address of the first mobile number in ptr's list of mobile numbers
        strcpy(newmobile->number,num);//num is stored at newmobile
        (newmobile->mnext)=head;
        (ptr->mptr)=newmobile;//newmobile is added to the list at its head position
    }
}

//Function to add a new mobile number or update an existing one of the contact at ptr.
void Mobile_Operations(struct contact* ptr)
{
    int _choice=0;
    printf("\n\tDo you wish to add a new number or update an existing one(Enter 1 for an update ,2 to add a new number and 3 to delete an old number):");
    if(scanf("%d",&_choice)!=1||(_choice!=1&&_choice!=2&&_choice!=3))//obtaining user's choice and checking its validity
    {
        getchar();//\n is cleared
        printf("\nPlease enter a valid choice!\n");
        return;
    }
    else
    {
        getchar();//\n is cleared
        struct mobile* found;//found will be used for pointing to the mobile number to be updated
        char match[SM];//match will be used for storing a user entered mobile number
        switch(_choice)
        {
            case 1:
                printf("\n\tEnter the existing number which you wish to update:");
                fgetline(match,SM,stdin,'\n');//the existing mobile number is obtained
                found=Search_Mobile(ptr,match);
                if(found==NULL)//if the existing mobile number is not found
                {
                    printf("\n The mobile number is not there as one of the mobile numbers of the contact.");
                    break;
                }
                printf("\n\tEnter the new number:");
                fgetline(match,SM,stdin,'\n');//new mobile number is obtained
                strcpy(found->number,match);//the old mobile number is replaced with the new one
                break;
            case 2:
                printf("\n\tEnter the new number:");
                fgetline(match,SM,stdin,'\n');//the new mobile number is obtained
                Add_New_Number(ptr,match);//the new mobile is added
                printf("\nSuccessfully Added");
                break;
            case 3:
                printf("\n\tEnter the existing number which you wish to delete:");
                fgetline(match,SM,stdin,'\n');//the existing mobile number is obtained
                found=Search_Mobile(ptr,match);
                if(found==NULL)//if the existing mobile number is not found
                {
                    printf("\n The mobile number is not there as one of the mobile numbers of the contact.");
                    break;
                }
                (ptr->mptr)=Delete_Mobile(ptr,match);//The match is deleted from the list
                break;
        }
        return;
    }
}

//Function to delete the mobile number match from the list of mobile numbers of contact at ptr
//It returns the new address of the first mobile number in the list of mobile number of contact at ptr.
//It is definitely known that match is in the list of mobile numbers of contact at ptr.
struct mobile* Delete_Mobile(struct contact* ptr,const char* match)
{
    struct mobile* mhead=ptr->mptr;//The address of the first mobile number is stored in mhead
    struct mobile* preceding_mobile;//Variable which points to the mobile number which precedes the mobile number at currentmobile
    struct mobile* currentmobile;//variable pointing to the current mobile number in loop
    if((mhead->mnext)==NULL)//A single mobile number cannot be deleted
    {
        printf("\nThere is only a single mobile number. It cannot be deleted.");
        return mhead;
    }
    else
    {
        if(strcmp(mhead->number,match)==0)//if match is the first mobile number in the liked list
        {
            currentmobile=mhead;
            mhead=mhead->mnext;//mhead is redefined
            free(currentmobile);//the old mhead is deleted
        }
        else
        {
            preceding_mobile=mhead;//Initialization before loop entry
            currentmobile=mhead->mnext;//Initialization before loop entry
            while(currentmobile!=NULL)//Loop for traversal
            {
                if(strcmp(currentmobile->number,match)==0)//if the mobile number at currentmobile is to be deleted
                    break;
                currentmobile=currentmobile->mnext;//loop update statement
                preceding_mobile=preceding_mobile->mnext;//loop update statement
            }
            preceding_mobile->mnext=currentmobile->mnext;//the mobile number at current mobile is delinked from the list
            free(currentmobile);//the mobile number at currentmobile is deleted
        }
    }
    printf("\nSuccessfully Deleted");
    return mhead;
}
//Function to update a contact in the linked list of contacts where the address of the first node is head
//It returns the head of the linked the list after the alterations
struct contact* Update_Single_Contact(struct contact* head)
{
    struct contact match;// a temporary contact is created statically
    struct mobile tempmobile;//a temporary mobile is created
    struct contact* ptr=&match;//ptr is declared as a pointer to match
    Initialize(ptr);//match is initialized
    ptr->mptr=&tempmobile;//tempmobile is match's mobile
    printf("\n\tEnter name:");
    fgetline(ptr->name,SN,stdin,'\n');//match's name is obtained
    printf("\n\tEnter mobile:");
    fgetline(tempmobile.number,SM,stdin,'\n');//value of tempmobile's number is obtained
    struct contact* loc=Find_Contact(head,match);//if a contact that resembles match is found , its address is stored in loc, else , loc is assigned NULL
    struct contact* temp=NULL;//temp will be used for deletion purposes later
    if(loc==NULL)//if no contact resembles match
    {
        printf("\nContact Not Found!!\n\n");
        return head;//the linked list's head is returned
    }
    else
    {
        printf("\nContact Found!!\n\n");
        Print_Node(loc);//The found contact is printed
        int choice=0;//variable for storing the user's choice
        printf("\tEnter 1 to update certain fields,2 to delete the contact and 0 for going back to main menu:");
        if(scanf("%d",&choice)!=1)//if an integer is not scanned
        {
            getchar();//\n is cleared
            printf("You have not entered a valid choice.Returning to main menu.\n\n");
            return head;//head of the linked list is returned
        }
        else if(choice>2||choice<0)//if choice is invalid
        {
            getchar();//\n is cleared
            printf("You have not entered a valid choice.Returning to main menu.\n\n");
            return head;//head of the linked list is returned
        }
        else
        {
            getchar();//\n is cleared
            int field_choice;//field_choice is used for deciding which field will be changed
            switch(choice)
            {
                case 0://return to main menu
                    printf("Returning to Main Menu.\n\n");
                    break;
                case 1:
                    printf("\n\tChoose one from the following.");
                    field_choice=Menu();//field_choice will be returned by the Menu() function
                    if(field_choice<0||field_choice>6)//invalid choice
                    {
                     printf("You have not entered a valid choice. Returning to main menu.\n\n");
                    }
                    else
                    {
                        switch(field_choice)
                        {
                        case 1://new name is obtained
                            printf("\tEnter new Name:");
                            fgetline(loc->name,SN,stdin,'\n');
                            break;
                        case 2://new organisation is obtained
                            printf("\tEnter new Organisation:");
                            fgetline(loc->organisation,SO,stdin,'\n');
                            break;
                        case 3://the Mobile_Operations function is called
                            Mobile_Operations(loc);
                            break;
                        case 4://new home address is obtained
                            printf("\tEnter new Home:");
                            fgetline(loc->home,SH,stdin,'\n');
                            break;
                        case 5://new pin code is obtained
                            printf("\tEnter new Pincode:");
                            fgetline(loc->pincode,SP,stdin,'\n');
                            break;
                        case 6://new state is obtained
                            printf("\tEnter new State:");
                            fgetline(loc->state,SS,stdin,'\n');
                            break;
                        }
                    }
                    break;
                case 2:
                    if(loc==head)//if the node to be deleted is the first node
                    {
                        head=head->next;//head is redefined as the second node
                        Dealloc_Memory(loc);//old head is deleted
                    }
                    else
                    {
                        temp=head;
                        while((temp->next)!=loc)//loop for traversing to find loc
                        {
                            temp=temp->next;
                        }
                        temp->next=loc->next;//delinking loc from the list
                        Dealloc_Memory(loc);//deleting loc
                    }
                    break;
            }
            return head;//head of the linked list is returned
        }
    }
}

//Function which will return the field choice of the user if it is valid.Else, it will return -1
int Menu()
{
    int _choice;
    printf("\n1.Name\n2.Organisation.\n3.Mobile\n4.Home\n5.Pincode\n6.State\n\tEnter your choice for the field:");
    if(scanf("%d",&_choice)!=1)
    {
        getchar();//\n is cleared
        return -1;//invalid choice
    }
    else if(_choice>6||_choice<1)
    {
        getchar();//\n is cleared
        return -1;
    }
    else
    {   getchar();//\n is cleared
        return _choice;//The choice is returned
    }
}

//Function interfaces with the user
int User_Interface()
{
    char RFile[100],WFile[100],Match[150],letter;//RFile is the file from which input is taken.WFile is the file into which output is printed.Match is used for obtaining a string from the user.letter is used for getting a character from the user.
    int field_choice;//field_choice will store user's choice for the field
    long insertion_position;//insertion_position will store the position where an insert operation is to be performed
    printf("\nEnter the name of the text file in which the contacts are stored(max 99 characters):");
    fgetline(RFile,100,stdin,'\n');//RFile is obtained
    char ch='Y';//ch will be used for exiting from the following loop
    int _choice;//_choice will store the user's choice from the list of operations that can be performed
    struct contact* head=Create_List(RFile);//The list of contacts is created
    if(head==NULL)
        return FAILURE;//Failed to create a list. Returns -1 indicating an error.
    while(ch=='Y'||ch=='y')
    {
        field_choice=0;
        insertion_position=1;
        //The list of operations is printed
        printf("\nThe list of operations are as follows:");
        printf("\n1.Print the list");
        printf("\n2.Delete particular nodes");
        printf("\n3.Sort the whole list");
        printf("\n4.Sort the nodes whose names begin with a certain letter");
        printf("\n5.Insert a new node into a given position");
        printf("\n6.Print a sublist with a given value of a field");
        printf("\n7.Find a contact(using name and a mobile number) and update or delete it.");
        printf("\n8.Exit\n\tEnter your choice:");
        if(scanf("%d",&_choice)!=1)//detection of invalid choice
        {
            ch='Y';//to go into the next iteration
            getchar();//\n is removed
            printf("\n You have not entered a valid choice.Please Try again.");
        }
        else{
            getchar();//\n is removed
            ch='Y';// by default, next iteration will be done unless _choice is 8
            switch(_choice)
            {
                case 1:
                    Print_List(head);//the list of contacts is printed
                    break;
                case 2:
                    printf("\nChoose one from the following.");
                    field_choice=Menu();//field_choice is obtained
                    if(field_choice==-1)//invalid field_choice
                    {
                     printf("Please enter a valid choice.");
                     continue;//Rest of the current iteration is skipped
                    }
                    printf("\tEnter the match:");
                    fgetline(Match,150,stdin,'\n');//The Match for field_choice is obtained
                    head=Delete_Node(head,field_choice,Match);//Contacts where the field corresponding to field_choice is Match are deleted
                    break;
                case 3:
                    printf("\nChoose one from the following.");
                    field_choice=Menu();//field_choice is obtained
                    if(field_choice==-1)//invalid field_choice
                    {
                     printf("\nPlease enter a valid choice.");
                     continue;//Rest of the current iteration is skipped
                    }
                    Sort_List(head,field_choice);//Sort is performed on the basis of field_choice
                    printf("\nSuccessfully Sorted.\n\n");
                    break;
                case 4:
                    printf("\tEnter the character:");//The letter with which a contact's name must begin in order to be sorted
                    scanf("%c",&letter);//letter is obtained
                    getchar();//\n is cleared
                    struct contactptr* chead=Create_List_Of_Pointers_Begin(head,letter);//The linked list of pointers to contacts whose names begin with letter is created
                    if(chead==NULL)
                    {
                        printf("\nFailed to allocate memory/No such names exist.");
                        continue;//Rest of the current iteration is skipped
                    }
                    Sort_Begin_Letter(chead);//The contacts whose names begin with letter are sorted on the basis of their names
                    printf("\nSuccessfully Sorted.\n\n");
                    Dealloc_Cpointer(chead);//The linked list of pointers to contacts which begin with letter is deleted
                    break;
                case 5:
                    printf("\tEnter desired position:");
                    if(scanf("%ld",&insertion_position)!=1)//The position at which the user wishes to place the new contact is obtained
                    {
                        getchar();//\n is cleared
                        printf("\nYou have not entered a valid position.");
                        continue;//Rest of the current iteration is skipped
                    }
                    getchar();//\n is cleared
                    head=Insert_Into(head,insertion_position);//A new contact is obtained and inserted at insertion_position
                    printf("\nSuccessfully Inserted.\n\n");
                    break;
                case 6:
                    printf("\nChoose one from the following.");
                    field_choice=Menu();//field_choice is obtained
                    if(field_choice==-1)//invalid field_choice
                    {
                     printf("\nPlease enter a valid choice.");
                     continue;//Rest of the current iteration is skipped
                    }
                    printf("\tEnter the match:");
                    fgetline(Match,150,stdin,'\n');//Match is obtained
                    Print_SubList(head,field_choice,Match);//The list of contacts where the field corresponding to field_choice is Match is printed
                    break;
                case 7:
                    head=Update_Single_Contact(head);//Update is performed
                    break;
                case 8:
                    ch='N';//User wishes to exit from the loop
                    break;
                default:
                    printf("\n You have not entered a valid choice.Please Try again.");
                    break;
            }
        }
    }
    printf("\nDo you wish to save your changes in a new file(Y|N)?");//asking the user whether he wishes to save the contacts in a file
    if((scanf("%c",&ch)==1)&&(ch=='Y'))
    {
        getchar();//\n is removed
        printf("\nEnter the name of the file:");
        fgetline(WFile,100,stdin,'\n');//The name of the file in which the contacts are to be saved is obtained
        Write_List(head,WFile);
    }
    Dealloc_List(head);//The memory allocated for storing the list of contacts is freed
    return SUCCESS;
}


