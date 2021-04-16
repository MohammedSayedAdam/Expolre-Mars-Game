#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
enum Direction
{
	north = 0,
	east = 1,
	south = 2,
	west = 3
};
class Map
{
	private:
	vector < vector<char> > map;
	int dimX, dimY;
	int Gold_Count;
	int Path_Count;
	char path[100];
	public:
	Map(int dimx, int dimy,int goco)
	{
		this->dimX = dimx;
		this->dimY = dimy;
		this->Gold_Count = goco;
		this->Path_Count = 0;
		srand((unsigned int)time(NULL));//to make intial time seed
		vector<char>temp;//to intial fill
		for (int i = 0; i < dimY; i++)
		{
			for (int j = 0; j < dimX; j++)
			{
				temp.push_back('?');
			}
			this->map.push_back(temp);
			temp.clear();
		}
	}	
	Map()
	{

	}
	void display()
	{
		/*for (size_t i = 0; i < Path_Count; i++)
		{
			cout << path[i] << "-->";
		}
		cout << endl;*/
		//display after creating map
		for (size_t i = 0; i < map.size(); i++)
		{
			cout << "+";
			for (size_t j = 0; j < map[i].size(); j++)
			{
				cout << "-+";
				if (j == map[i].size() - 1)
					cout << endl;
			}
			cout << "|";
			for (size_t j = 0; j < map[i].size(); j++)
			{
				if (j != map[i].size() - 1)
					cout << map[i][j] << "|";
				else
					cout << map[i][j] << "|" << endl;
			}
		}
		cout << "+";
		for (size_t j = 0; j < dimX; j++)
		{
			cout << "-+";
			if (j == dimX - 1)
				cout << endl;
		}
		
	}
	int Random_Heading()
	{
		 return Fun_Random_Generation(4);//0-3
	}
	Direction Move_First_step(int &x,int &y)
	{
		//random heading  step no 3 to tell me the head of charcter >||<||^||v
		int r = Random_Heading();
		Direction dir = north;
		if (r == 0)//north
		{
			map[y - 1][x] = ' ';
			y--;
			dir = north;
		}
		else if (r == 1)//east
		{
			map[y][x + 1] = ' ';
			x++;
			dir = east;
		}
		else if (r == 2)//south
		{
			map[y + 1][x] = ' ';
			y++;
			dir = south;
		}
		else if (r == 3)//west
		{
			map[y][x - 1] = ' ';
			x--;
			dir = west;
		}
		return dir;
	}
	void Turn_Around(Direction &dir,int &x,int &y)
	{
		if (dir == north)
		{
			dir = south;
			if (map[y + 1][x] != '*')
				map[y + 1][x] = ' ';
			y++;
		}
		else if (dir == east)
		{
			dir = west;
			if (map[y][x - 1] != '*')
				map[y][x - 1] = ' ';
			x--;
		}
		else if (dir == south)
		{
			dir = north;
			if (map[y - 1][x] != '*')
				map[y - 1][x] = ' ';
			y--;
		}
		else if (dir == west)
		{
			dir = east;
			if (map[y][x + 1] != '*')
				map[y][x + 1] = ' ';
			x++;
		}
	}
	void Keep_Walk_till_Gold(int &x,int &y,Direction dir)
	{
		while (Gold_Count > 0)
		{
			int Gold_Genr = Fun_Random_Generation(10);//generate 10%  (0-9) chance to put gold
			if (Gold_Genr == 0)
			{
				map[y][x] = '*';
				Gold_Count--;
				if (Gold_Count == 0)
					break;
			}


			////////////////////////////////////////////////////////////////////////////////////////////////
			//                                       north direction                                      //                                      
			////////////////////////////////////////////////////////////////////////////////////////////////


			if (dir == 0)//north
			{
				int d = Fun_Random_Generation(10);
				///left of north
				if ((d == 0|| d == 1) && x > 0) // change moving  to west
				{
					dir = west; //change direction to east
					path[Path_Count] = 'l';//add char to our path
					Path_Count++;//update path
					if (map[y][x - 1] != '*')//if it as a gold i `ll leave it with ('*') character
						map[y][x - 1] = ' ';
					x--;//update x axes to negative step
				}
				///right of north
				else if ((d == 8  || d == 9) && x < dimX - 1)//change move to east (right)
				{
					dir = east;//change direction to east
					path[Path_Count] = 'r';//add char to our path
					if (map[y][x + 1] != '*')
						map[y][x + 1] = ' ';
					Path_Count++;//update path
					x++;//update x axes to positive step
				}
				//along of north
				else if (y > 0)
				{
					dir = north;//change direction to north
					if (map[y - 1][x] != '*')
						map[y - 1][x] = ' ';
					path[Path_Count] = 'm';//add char to our path
					Path_Count++;//update path
					y--;
				}
				//turn direction
				else if (y == 0)
				{
					dir = north;
					Turn_Around(dir, x, y);
				}
			}



			////////////////////////////////////////////////////////////////////////////////////////////////
			//                                       east direction                                       //
			////////////////////////////////////////////////////////////////////////////////////////////////



			else if (dir == 1)//east
			{
				int d = Fun_Random_Generation(10);
				//left of east
				if ((d == 0  || d == 1) && y > 0) // change moving  to west (left)
				{
					dir = north; //change direction to 
					path[Path_Count] = 'l';//add char to our path
					Path_Count++;//update path
					if (map[y - 1][x] != '*')
						map[y - 1][x] = ' ';
					y--;//update y axes to negative step
				}
				//right of east
				else if ((d == 8 || d == 9) && y < dimY - 1)//change move to east (right)
				{
					dir = south;//change direction to 
					path[Path_Count] = 'r';//add char to our path
					if (map[y + 1][x] != '*')
						map[y + 1][x] = ' ';
					Path_Count++;//update path
					y++;//update y axes to positive step
				}
				//move along east
				else if (x < dimX - 1)
				{
					dir = east;//change direction to 
					if (map[y][x + 1] != '*')
						map[y][x + 1] = ' ';
					path[Path_Count] = 'm';//add char to our path
					Path_Count++;//update path
					x++;
				}
				else if (x == dimX - 1)
				{
					dir = east;
					Turn_Around(dir, x, y);
				}
			}


			////////////////////////////////////////////////////////////////////////////////////////////////
			//                                    south direction                                         //
			////////////////////////////////////////////////////////////////////////////////////////////////


			else if (dir == 2)//south
			{
				int d = Fun_Random_Generation(10);
				if ((d == 0 || d == 1) && x < dimX - 1) // change moving  left
				{
					dir = east; //change direction 
					path[Path_Count] = 'l';//add char to our path
					Path_Count++;//update path
					if (map[y][x + 1] != '*')
						map[y][x + 1] = ' ';
					x++;//update x axes to positive step
				}
				else if ((d == 8 || d == 9) && x > 0)//change move to  (right)
				{
					dir = west;//change direction  
					path[Path_Count] = 'r';//add char to our path
					if (map[y][x - 1] != '*')
						map[y][x - 1] = ' ';
					Path_Count++;//update path
					x--;//update x axes to negative step
				}
				else if (y < dimY - 1)
				{
					dir = south;//change direction  
					if (map[y + 1][x] != '*')
						map[y + 1][x] = ' ';
					path[Path_Count] = 'm';//add char to our path
					Path_Count++;//update path
					y++;
				}
				else if (y == dimY - 1)
				{
					dir = south;
					Turn_Around(dir, x, y);
				}
			}



			////////////////////////////////////////////////////////////////////////////////////////////////
			//                                        west direction                                      //
			////////////////////////////////////////////////////////////////////////////////////////////////



			else if (dir == 3)//west
			{
				int d = Fun_Random_Generation(10);
				if ((d == 0 || d == 1) && y < dimY-1) // change moving  to left
				{
					dir = south; //change direction to east
					path[Path_Count] = 'l';//add char to our path
					Path_Count++;//update path
					if (map[y + 1][x] != '*')
						map[y + 1][x] = ' ';
					y++;
				}
				else if ((d == 8 || d == 9) && y > 0)//change move  (right)
				{
					dir = north;//change direction 
					path[Path_Count] = 'r';//add char to our path
					if (map[y - 1][x] != '*')
						map[y - 1][x] = ' ';
					Path_Count++;//update path
					y--;
				}
				else if (x > 0)
				{
					dir = west;//change direction to north
					if (map[y][x - 1] != '*')
						map[y][x - 1] = ' ';
					path[Path_Count] = 'm';//add char to our path
					Path_Count++;//update path
					x--;
				}
				else if (x == 0)
				{
					dir = west;
					Turn_Around(dir, x, y);
				}
			}//else west


		}//while


	}//function
	void Walk_Around()
	{
		int x = Xavg(), y = Yavg();
		
		Direction dir = Move_First_step(x, y);//step no 4 random heading direction Keep moving in the current direction and change the cells to be empty spaces as we
		//step no 5
		path[Path_Count] = 'm';
		Path_Count++;
		Keep_Walk_till_Gold( x, y, dir);
	}
	void resize(int dimx, int dimy, char ch)
	{

	}
	void setObject(int x, int y, char ch)
	{
		map[y][x] = ch;
	}
	char getObject(int x, int y)
	{
		return map[y][x];
	}
	bool isEmpty(int x, int y)
	{
		return (map[y][x] == ' ');
	}
	bool isHill(int x, int y)
	{
		return (map[y][x] == '&');
	}
	bool isTrap(int x, int y)
	{
		return (map[y][x] == '#');
	}
	bool isInsideMap(int x, int y)
	{
		return (x <= dimX - 1 && x>=0 && y <= dimY - 1 && y>=0);
	}
	int getDimX()
	{
		return dimX;
	}
	int getDimY()
	{
		return dimY;
	}
	int Fun_Random_Generation(int scale)
	{
		return rand() % scale;
	}
	void genIntialMap()
	{
		for (size_t i = 0; i < dimY; i++)
		{
			for (size_t j = 0; j < dimX; j++)
			{
				//generatian of 2 charc...
				int c = Fun_Random_Generation(10);
				if (c == 0 || c == 1 || c == 2)
					map[i][j] = '#';/*for trap*/
				else if (c == 0 || c == 1 || c == 5)
					map[i][j] = '&';/*for Hill*/
				else
					map[i][j] = ' ';//for more spaces
			}
		}
		
	}
	int Xavg()
	{
		int x = dimX / 2;
		if (dimX % 2 != 0)
			x++;
		return x-1;//-1 as it array index
	}
	int Yavg()
	{
		int y = dimY / 2;
		if (dimY % 2 != 0)
			y++;
		return y-1;//-1 as it array index
	}
	void X_Y_Center(int &x, int &y)
	{
		x = Xavg(); y = Yavg();
	}
	vector<vector<char>> Get_Intial_Map()
	{
		return map;
	}
	vector<vector<char>> Get_Final_Map()
	{
	    // step 1: in algorithm generate intial map with three charcters(#for trap, &for hill, ' ' space)
		genIntialMap();
		//step 2: in algorithm make the centred cell is empty
		int x = Xavg(),/*to get average of the x points*/ y = Yavg();/*to get average of the y points*/
		map[y][x] = ' ';//set the centerd point it empty
		//for draw map till now
		/*for (size_t i = 0; i < map.size(); i++)
		{
		cout << "+";
		for (size_t j = 0; j < map[i].size(); j++)
		{
		cout << "-+";
		if (j == map[i].size() - 1)
		cout << endl;
		}
		cout << "|";
		for (size_t j = 0; j < map[i].size(); j++)
		{
		if (j != map[i].size() - 1)
		cout << map[i][j] << "|";
		else
		cout << map[i][j] << "|" << endl;
		}
		}
		cout << "+";
		for (size_t j = 0; j < dimX; j++)
		{
		cout << "-+";
		if (j == dimX - 1)
		cout << endl;
		}*/
		//step 3: in algorithm 
		//first do a random  direction from enum
		Walk_Around();
		//cout << "--------------------------------------------" << endl;
		//display the path which he walked in without directions
		return map;
	}
};
class Rover
{
private:
	int x, y;
	Direction heading;
	char objectUnderRover;
	Map* p_mars; //a pointer to the map for Mars
	Map mapper; //a map that keeps track of observed cells so far
	vector<vector<char>> Swapping_Map;
	vector<vector<char>> Final_Map;
	vector<char> path;
	int Score, Gold_Counter;
public:
	
	Rover(Map mapper, int x, int y,int g)
	{
		//this->p_mars = p_mars;
		this->mapper = mapper;
		this->x = mapper.Xavg();
		this->y = mapper.Xavg();
		this->Swapping_Map = this->mapper.Get_Intial_Map();//intialization of vector for foreground map
		this->p_mars = &mapper;
		this->objectUnderRover = ' ';
		this->heading = north;
		this->Score = 0;
		this->Gold_Counter = g;
	}
	void land(Map& mars) //links a map of Mars to a Rover
	{
		Final_Map = mapper.Get_Final_Map();//background map
		int head_random;
		mapper.X_Y_Center(x, y);
		head_random = mapper.Random_Heading();
		heading = get_head(head_random);
		Swapping_Map[y][x] = objectUnderRover;
		Show_Three_cells();
		string com_seq;
		displayMapper();
		cin >> com_seq;//verify input
		int c = 0; bool cont = true;
		while (cont)
		{
			if (c != 0)
			{
				system("CLS");
				cout << "--__--__ Mars Rover Mapper__--__--" << endl;
				displayMapper();
				cin >> com_seq;
			}
			for (int i = 0; i < com_seq.size(); i++)
			{
				if (executeCommand(com_seq[i]))
				{
					if (Swapping_Map[y][x] == '@' || com_seq[i] == 'Q')
					{
						cont = false;
						system("CLS");
						cout << "--__--__ Mars Rover Mapper__--__--" << endl;
						displayMapper();
						cout << com_seq << endl;
						cout << "Your--_--Score is : " << Score << endl;
						cout << "Mission Failed!!" << endl;
						break;
					}
					if (com_seq.size() - 1 == i)
					{
						cont = true;
						c++;
						break;
					}
					if (Gold_Counter == 0)
					{
						cout << "Winnnnnnnnnnnnnnnnnner ---- Winnnnnnnnnnnnnnnnnner -- Winnnnnnnnnnnnnnnnnner" << endl;
						cont = false;
						break;
					}
					system("CLS");
					cout << "--__--__ Mars Rover Mapper__--__--" << endl;
					displayMapper();
					
				}
				else if (!executeCommand(com_seq[i]) || Swapping_Map[y][x] == '@')
				{
					system("CLS");
					cout << "--__--__ Mars Rover Mapper__--__--" << endl;
					displayMapper();
					cout << com_seq << endl;
					cout << "Mission Failed!!" << endl;
					cont = false;
					break;
				}
			}
		}
	}
	void Show_Three_cells()
	{
		//Final_Map =  mapper.Get_Final_Map();
		if (heading == north && mapper.isInsideMap(x, y - 1)/*up*/
			&& mapper.isInsideMap(x + 1, y - 1)/*up right*/
			&& mapper.isInsideMap(x - 1, y - 1))/*up left*/
		{
			Swapping_Map[y - 1][x] = Final_Map[y - 1][x];
			Swapping_Map[y - 1][x - 1] = Final_Map[y - 1][x - 1];
			Swapping_Map[y - 1][x + 1] = Final_Map[y - 1][x + 1];
		}
		else if (heading == east
				&& mapper.isInsideMap(x + 1, y - 1)
				&& mapper.isInsideMap(x + 1,  y    )
				&& mapper.isInsideMap(x + 1, y + 1))
		{
			Swapping_Map[y - 1][x + 1] = Final_Map[y - 1][x + 1];
			Swapping_Map[y][x + 1] = Final_Map[y][x + 1];
			Swapping_Map[y + 1][x + 1] = Final_Map[y + 1][x + 1];
		}
		else if (heading == south
			&& mapper.isInsideMap(x + 1, y + 1)
			&& mapper.isInsideMap(x, y + 1)
			&& mapper.isInsideMap(x - 1, y + 1))
		{
			Swapping_Map[y + 1][x] = Final_Map[y + 1][x];
			Swapping_Map[y + 1][x - 1] = Final_Map[y + 1][x - 1];
			Swapping_Map[y + 1][x + 1] = Final_Map[y + 1][x + 1];
		}
		else if (heading == west
			&& mapper.isInsideMap(x - 1, y - 1)
			&& mapper.isInsideMap(x - 1, y)
			&& mapper.isInsideMap(x - 1, y + 1))
		{
			Swapping_Map[y - 1][x - 1] = Final_Map[y - 1][x - 1];
			Swapping_Map[y][x - 1] = Final_Map[y][x - 1];
			Swapping_Map[y + 1][x - 1] = Final_Map[y + 1][x - 1];
		}
		else if (x == 0 )
		{
			if (heading == south)
			{
				Swapping_Map[y + 1][x] = Final_Map[y + 1][x];
				Swapping_Map[y + 2][x] = Final_Map[y + 2][x];
				Swapping_Map[y + 3][x] = Final_Map[y + 3][x];
			}
			else if(heading == east)
			{
				Swapping_Map[y][x + 1] = Final_Map[y][x + 1];
				Swapping_Map[y][x + 2] = Final_Map[y][x + 2];
				Swapping_Map[y][x + 3] = Final_Map[y][x + 3];
			}
		}
	}
	Direction get_head(int ran)
	{
		if (ran == 0)//north
		{
			objectUnderRover = '^';
			return north;
		}
		else if (ran == 1)//east
		{
			objectUnderRover = '>';
			return east;
		}
		else if (ran == 2)//south
		{
			objectUnderRover = 'v';
			return south;
		}
		else if (ran == 3)//west
		{
			objectUnderRover = '<';
			return west;
		}

	}
	bool turnLeft()
	{
		if (heading == north)
		{
			if (x > 0)
			{
				if (mapper.isTrap(x - 1, y))
				{
					return true;
				}
				else if (mapper.isEmpty(x - 1, y))
				{
					return true;
				}
				else if (Final_Map[y][x - 1] == '*')
				{
					return true;
				}
			}
			return false;
		}
		else if (heading == east)
		{
			if (y > 0)
			{
				if (mapper.isTrap(x, y - 1))
				{
					return true;
				}
				else if (mapper.isEmpty(x, y - 1))
				{
					return true;
				}
				else if (Final_Map[y - 1][x] == '*')
				{
					return true;
				}
			}
			return false;
		}
		else if (heading == south)
		{
			if (x < mapper.getDimX() - 1)
			{
				if (mapper.isTrap(x + 1, y))
				{
					return true;
				}
				else if (mapper.isEmpty(x + 1, y))
				{
					return true;
				}
				else if (Final_Map[y][x + 1] == '*')
				{
					return true;
				}

			}
			return false;
		}
		else if (heading == west)
		{
			if (y < mapper.getDimY() - 1)
			{
				if (mapper.isTrap(x, y + 1))
				{
					return true;
				}
				else if (mapper.isEmpty(x + 1, y))
				{
					return true;
				}
				else if (Final_Map[y][x + 1] == '*')
				{
					return true;
				}

			}
			return false;
		}
		return false;
	}
	bool turnRight()
	{
		if (heading == north)
		{
			
		}
		else if (heading == east)
		{

		}
		else if (heading == east)
		{

		}
		else if (heading == east)
		{

		}
		return true;
	}
	bool move()
	{
		if (heading == north)
		{
			if (y > 0)
			{
				heading = north;
				if (mapper.isTrap(x, y - 1))
				{
					return true;
				}
				else if (mapper.isEmpty(x, y - 1))
				{
					return true;
				}
				else if (mapper.getObject(x, y - 1) == '*')
				{
					return true;
				}
			}
		}
		else if (heading == east)
		{
			if (x<mapper.getDimX() - 1)
			{
				heading = east;
				if (mapper.isTrap(x + 1, y))
				{
					return true;
				}
				else if (mapper.isEmpty(x + 1, y))
				{
					return true;
				}
				else if (mapper.getObject(x + 1, y) == '*')
				{
					return true;
				}
			}
		}
		else if (heading == south)
		{
			if (y<mapper.getDimY() - 1)
			{
				heading = south;
				if (mapper.isTrap(x, y + 1))
				{
					return true;
				}
				else if (mapper.isEmpty(x, y + 1))
				{
					return true;
				}
				else if (mapper.getObject(x, y + 1) == '*')
				{
					return true;
				}
			}
		}
		else if (heading == west)
		{
			if (x>0)
			{
				if (mapper.isTrap(x - 1, y))
				{
					return true;
				}
				else if (mapper.isEmpty(x - 1, y))
				{
					return true;
				}
				else if (mapper.getObject(x - 1, y) == '*')
				{
					return true;
				}
			}
		}
	}
	void displayMapper()
	{
		cout << "Score is : " << Score << endl;
		for (size_t i = 0; i < mapper.getDimY(); i++)
		{
			cout << "+";
			for (size_t j = 0; j < mapper.getDimX(); j++)
			{
				cout << "-+";
				if (j == mapper.getDimX() - 1)
					cout << endl;
			}
			cout << "|";
			for (size_t j = 0; j < mapper.getDimX(); j++)
			{
				if (j != mapper.getDimX() - 1)
					cout <<Swapping_Map[i][j] << "|";
				else
					cout << Swapping_Map[i][j] << "|" << endl;
			}
		}
		cout << "+";
		for (size_t j = 0; j < mapper.getDimX(); j++)
		{
			cout << "-+";
			if (j == mapper.getDimX() - 1)
				cout << endl;
		}
		cout << "Mission: Get all the golds!!, Do not get trapped!!" << endl;
		cout << "L = Turn Left, R = Turn Right, M = Move, Q = Quit" << endl;
		cout << "& = Hill # = Trap *= Gold" << endl;
		cout << "Example Sequence: LMMMMLLRRRLRMMRLRLML" << endl;
		cout << "Enter command sequence =>";
	}
	void turn_Right()
	{
		if (heading == south)
		{
			heading = west;
			if (mapper.isTrap(x - 1, y))
			{
				Swapping_Map[y][x - 1] = '@';
				Swapping_Map[y][x] = ' ';
				x--;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x - 1, y))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				x--;
				Swapping_Map[y][x] = '<';
				Show_Three_cells();
			}
			else if (Final_Map[y][x - 1] == '*')
			{
				mapper.setObject(x - 1, y, ' ');//set the position i left to space as i taked one gold;
				Swapping_Map[y][x] = ' ';
				this->Score += 1;
				this->Gold_Counter -= 1;
				x--;
				Swapping_Map[y][x] = '<';
				Show_Three_cells();
			}
		}
		else if (heading == west)
		{
			heading = north;
			if (mapper.isTrap(x, y - 1))
			{
				Swapping_Map[y - 1][x] = '@';
				Swapping_Map[y][x] = ' ';
				y--;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x, y - 1))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				y--;
				Swapping_Map[y][x] = '^';
				Show_Three_cells();
			}
			else if (Final_Map[y - 1][x] == '*')
			{
				mapper.setObject(x, y - 1, ' ');
				Swapping_Map[y][x] = ' ';
				Swapping_Map[y - 1][x] = ' ';
				this->Score += 1;
				this->Gold_Counter -= 1;
				y--;
				Swapping_Map[y][x] = '^';
				Show_Three_cells();
			}
		}
		else if (heading == north)
		{
			heading = east;
			if (mapper.isTrap(x + 1, y))
			{
				Swapping_Map[y][x + 1] = '@';
				Swapping_Map[y][x] = ' ';
				x++;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x + 1, y))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				x++;
				Swapping_Map[y][x] = '>';
				Show_Three_cells();
			}
			else if (Final_Map[y][x + 1] == '*')
			{

				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x + 1, y, ' ');
				Swapping_Map[y][x] = ' ';
				x++;
				Swapping_Map[y][x] = '>';
				Show_Three_cells();
			}
		}
		else if (heading == east)
		{
			heading = south;

			if (mapper.isTrap(x, y + 1))
			{
				Swapping_Map[y + 1][x] = '@';
				Swapping_Map[y][x] = ' ';
				y++;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x + 1, y))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				y++;
				Swapping_Map[y][x] = 'v';
				Show_Three_cells();
			}
			else if (Final_Map[y][x + 1] == '*')
			{

				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x + 1, y, ' ');
				Swapping_Map[y][x] = ' ';
				y++;
				Swapping_Map[y][x] = 'v';
				Show_Three_cells();
			}
		}
	} 
	void turn_Left()
	{
		if (heading == north)
		{
			heading = west;
			if (mapper.isTrap(x - 1, y))
			{
				Swapping_Map[y][x - 1] = '@';
				Swapping_Map[y][x] = ' ';
				x--;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x - 1, y))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				x--;
				Swapping_Map[y][x] = '<';
				Show_Three_cells();
			}
			else if (Final_Map[y][x - 1] == '*')
			{
				mapper.setObject(x - 1, y, ' ');//set the position i left to space as i taked one gold;
				Swapping_Map[y][x] = ' ';
				this->Score += 1;
				this->Gold_Counter -= 1;
				x--;
				Swapping_Map[y][x] = '<';
				Show_Three_cells();
			}
		}
		else if (heading == east)
		{
			heading = north;
			if (mapper.isTrap(x, y - 1))
			{
				Swapping_Map[y][x] = ' ';
				y--;
				Swapping_Map[y][x] = '@';
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x, y - 1))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				y--;
				Swapping_Map[y][x] = '^';
				Show_Three_cells();
			}
			else if (Final_Map[y - 1][x] == '*')
			{
				mapper.setObject(x, y - 1, ' ');
				Swapping_Map[y - 1][x] = ' ';
				Swapping_Map[y][x] = ' ';
				this->Score += 1;
				this->Gold_Counter -= 1;
				y--;
				Swapping_Map[y][x] = '^';
				Show_Three_cells();
			}
		}
		else if (heading == south)
		{
			heading = east;
			if (mapper.isTrap(x + 1, y))
			{
				Swapping_Map[y][x + 1] = '@';
				Swapping_Map[y][x] = ' ';
				x++;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x + 1, y))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				x++;
				Swapping_Map[y][x] = '>';
				Show_Three_cells();
			}
			else if (Final_Map[y][x + 1] == '*')
			{

				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x + 1, y, ' ');
				Swapping_Map[y][x] = ' ';
				x++;
				Swapping_Map[y][x] = '>';
				Show_Three_cells();
			}
		}
		else if (heading == west)
		{
			heading = south;

			if (mapper.isTrap(x, y + 1))
			{
				Swapping_Map[y + 1][x] = '@';
				Swapping_Map[y][x] = ' ';
				y++;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x + 1, y))
			{
				//return my position to space as i move step to left
				Swapping_Map[y][x] = ' ';
				y++;
				Swapping_Map[y][x] = 'v';
				Show_Three_cells();
			}
			else if (Final_Map[y][x + 1] == '*')
			{

				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x + 1, y, ' ');
				Swapping_Map[y][x] = ' ';
				y++;
				Swapping_Map[y][x] = 'v';
				Show_Three_cells();
			}
		}
	}
	void Move()
	{
		if (heading == north)
		{
			heading = north;
			if (mapper.isTrap(x, y - 1))
			{
				Swapping_Map[y - 1][x] = '@';
				Swapping_Map[y][x] = ' ';
				y--;
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x, y - 1))
			{
				Swapping_Map[y][x] = ' ';
				y--;
				Swapping_Map[y][x] = '^';
				Show_Three_cells();
			}
			else if (mapper.getObject(x, y - 1) == '*')
			{
				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x, y - 1, ' ');
				Swapping_Map[y][x] = ' ';
				y--;
				Swapping_Map[y][x] = '^';
				Show_Three_cells();
			}
		}
		else if (heading == east)
		{
			heading = east;
			if (mapper.isTrap(x + 1, y))
			{
				Swapping_Map[y][x] = ' ';
				x++;
				Swapping_Map[y][x] = '@';
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x + 1, y))
			{
				Swapping_Map[y][x] = ' ';
				x++;
				Swapping_Map[y][x] = '>';//return my position to space as i move step to left
				Show_Three_cells();
			}
			else if (mapper.getObject(x + 1, y) == '*')
			{
				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x + 1, y, ' ');
				Swapping_Map[y][x] = ' ';
				x++;
				Swapping_Map[y][x] = '>';
				Show_Three_cells();
			}
		}
		else if (heading == south)
		{
			heading = south;
			if (mapper.isTrap(x, y + 1))
			{
				Swapping_Map[y][x] = ' ';
				y++;
				Swapping_Map[y][x] = '@';
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x, y + 1))
			{
				Swapping_Map[y][x] = ' ';
				y++;
				Swapping_Map[y][x] = 'v';//return my position to space as i move step to left
				Show_Three_cells();
			}
			else if (mapper.getObject(x, y + 1) == '*')
			{
				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x, y + 1, ' ');
				Swapping_Map[y][x] = ' ';
				y++;
				Swapping_Map[y][x] = 'v';
				Show_Three_cells();
			}
		}
		else if (heading == west)
		{
			heading = west;
			if (mapper.isTrap(x - 1, y))
			{
				Swapping_Map[y][x] = ' ';
				x--;
				Swapping_Map[y][x] = '@';
				Show_Three_cells();
			}
			else if (mapper.isEmpty(x - 1, y))
			{
				Swapping_Map[y][x] = ' ';
				x--;
				Swapping_Map[y][x] = '<';//return my position to space as i move step to left
				Show_Three_cells();
			}
			else if (mapper.getObject(x - 1, y) == '*')
			{
				this->Score += 1;
				this->Gold_Counter -= 1;
				mapper.setObject(x - 1, y, ' ');
				Swapping_Map[y][x] = ' ';
				x--;
				Swapping_Map[y][x] = '<';
				Show_Three_cells();
			}
		}
	}
	bool executeCommand(char command)
	{
		if (command == 'L')
		{
			if (turnLeft())
			{
				turn_Left();
				path.push_back('L');
				cout << "excuted" << endl;
				return true;
			}
		}
		else if (command == 'M')
		{
			if (move())
			{
				Move();
				path.push_back('M');
				cout << "excuted" << endl;
				return true;
			}
		}
		else if (command == 'R')
		{
			if (turnRight())
			{
				turn_Right();
				path.push_back('R');
				cout << "excuted" << endl;
				return true;
			}
		}
		return false;
	}
};
void WelcomeScreen(short &X, short  &Y, short &G)
{
	cout << "Let's Explore Mars..." << endl;
	cout << "Mars dimension X => "; cin >> X;
	cout << "Mars dimension Y => "; cin >> Y;
	cout << "No of Golds => "; cin >> G; cout << endl;
	cout << "--__--__ Mars Rover Mapper__--__--" << endl;
}


int main()
{
	short x, y, g;
	WelcomeScreen(x, y, g);
	Map map(x, y, g);
	Rover rove(map, x, y, g);
	rove.land(map);
	system("pause");
	return 0;
}