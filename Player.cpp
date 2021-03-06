#include "Player.hpp"

Player::Player(Game *g, Floor* f, int i, int j, const string n, int l, 
	       const double r,
	       const int s, int va, const Weapon w) :
  People(f,i,j,'>',l,r,s,va,w), name(n),game(g){}

Player::~Player(){}

void Player::setSymbole(char s){ symbole = s; }

void Player::print() const {
  cout << BOLDYELLOW << getSymbole() << RESET;
}
//methode pour regarder les elements du joueur
void Player::lookbag()const{
  if(bag.size()<=0)
    cout <<BOLDCYAN<<"your bag is empty"<<RESET<<endl;
  else {
    cout <<BOLDCYAN<<"your bag contains : "<<RESET<<endl;
    for(int i(0); i<bag.size(); i++)
      cout <<BOLDCYAN<< bag[i].getName() << " | ";
    cout<<RESET <<endl;
  }
}
//methode pour ajouter des elements dans le sac on regardesi le sac n'est pas plein on ajoute sinon on doit supprimer un item
void Player::Add_item_bag( Item &item){
  char c;
  if(bag.size()<MAX_ITEM)
    bag.push_back(item);
  else{
    cout <<RED<<"Your bag is full remove an item if you want to add it"<<RESET<<endl;
    cout <<RED<<"tape 'y' if you want remove something or other button if not "<<RESET<<endl;

    system("stty raw");
    c = getchar();
    cout <<endl;
    system("stty cooked");
    if (c=='y')
      remove_item_bag();

  }
}
void Player::remove_item_bag(){
  if(bag.size()<=0)
    cout <<"your bag is empty, you can't remove an item"<<endl;
  else{
    cout<<"choice the number of the item wich you want remove"<<endl;
    lookbag();
    int i=0;
    cin >>i ;
    while(i<0 ||i>=bag.size())
      {
	cout <<"Wrong number, this item does not exist in your bag "<<endl;
	cout <<"please put a valid number"<<endl;
	cin >>i ;
      }

    cout<<"you have choosen this item: "<<CYAN<<bag[i].getName()<<RESET<<" it will be remove in your bag"<<endl;
    bag.erase(bag.begin()+ i);

    lookbag();
  }
}

void Player::change_Weapon(){
  if(bag.size()<=0)
    cout <<"your bag is empty, you can't change your weapon"<<endl;
  else{
    bool b = true;
    while(b){
      lookbag();
      cout << "enter the index of the weapon you want to equip"<<endl;
      int i;
      cin >> i;
      if(i>=0 && i < bag.size() && bag[i].typeOf() != WEAPON)
	b = false;
      if(!b){
	//setWeapon(((Weapon&)bag[i]).getAttack()); //doesnt work yet 
	cout<<BOLDGREEN<<((Weapon&)bag[i]).getName()<<" equiped."<<RESET<<endl;
      }
    }
  }
}

void Player::usePotionFromBag(){
  if(bag.size()<=0)
    cout <<"your bag is empty, you don't have any potion"<<endl;
  else{
    bool b = true;
    while(b){
      lookbag();
      cout << "enter the index of the potion you want to drink"<<endl;
      int i;
      cin >> i;
      if(i>=0 && i < bag.size() && (bag[i].typeOf() != POSION) ||
	 (bag[i].typeOf() != RESI_UP) ||
	 (bag[i].typeOf() != RESI_DOWN) ||
	 (bag[i].typeOf() != HEALING))
	b = false;
      if(!b){
	if(bag[i].typeOf() != POSION)
	  use((Posion&)bag[i]);
	else if(bag[i].typeOf() != RESI_UP)
	  use((ResiUpPotion&)bag[i]);
	else if(bag[i].typeOf() != RESI_DOWN)
	  use((ResiDownPotion&)bag[i]);
	else if(bag[i].typeOf() != HEALING)
	  use((HealingPotion&)bag[i]);
      }
    }
  }
}

const string Player::getName() const { return name; }

void Player::turn() {
  char c = 0;
  bool b = false, bb = false;
  while(!b || !bb){
    system("stty raw");
    c = getchar();
    system("stty cooked");
    cout << endl;
    if(c != 'o' && c != 'k' && c != 'l' && c != 'm' && c != 'h' && c != 'q' && c!='i' && c!='w' && c!='c' && c!='a' && c!='p')
      cout << RED << "Wrong command, try again : k(left), o(up), l(down), m(right), i(list_of_item), w(your Weapon), c(change weapon), alphabet(a), use potion stored in the bag(p), h(help), q(quit)\n" << RESET;
    else
      b = true;
    if(c == 'h'){
      cout << "To move on the game, use the following commands :"<<endl;
      cout << "\'k\' - left " << endl;
      cout << "\'o\' - up " << endl;
      cout << "\'l\' - down " << endl;
      cout << "\'m\' - right " << endl;
      cout << "\'q\' - quit " << endl;
      cout << "\'i\' - list of your Item " << endl;
      cout << "\'w\' - your Weapon " << endl;
      cout << "\'a\' - show the alaphabet " << endl;
      cout << "\'c\' - change your Weapon " << endl;
      cout << "\'p\' - use a potion store in the bag " << endl;
    }
    else if (c=='i')
      lookbag();
    else if (c=='c')
      change_Weapon();
    else if (c=='p')
      usePotionFromBag();
    else if (c=='a'){
      cout <<BOLDWHITE << "ALPHABET"<<RESET<<endl;
      cout << "# - wall" <<endl<<". - empty"<<endl<<"X - source"<<endl;
      cout <<"</>/^/v - player"<<endl<<"H - healing potion"<<endl;
      cout <<"h - posion"<<endl<<"R - potion resi up"<<endl;
      cout <<"r - potion resi down"<<endl<<"? - unknown object"<<endl;
      cout<<"m - monster"<<endl<<"M - monster2"<<endl;
      cout <<"w - warrior"<<endl<<"W - warrior2"<<endl;
      cout<<"n - ninja"<<endl<<"N - ninja2"<<endl;
      cout<<"c - cavalier"<<endl<<"C - cavalier2"<<endl;
      cout <<"j - shuriken"<<endl<<"s - sword"<<endl;
      cout <<"S - sword2"<<endl<<"U - stairs up"<<endl;
      cout<<"D - stairs down"<<endl<<"z - magician"<<endl<<"Z - magician2"<<endl;
    }else if (c=='w')
      cout << GREEN << "the weapon you use is: "<<getWeapon().getName()<<RESET<<endl;
    else if(c == 'q')
      exit(0);
    else if(c == 'o' || c == 'k'|| c == 'l'|| c == 'm') //a move
      bb = true;
  }
  move(c);
}

void Player::move(char c){
  if(c == 'k'){
    if(j > 0){ //not out of bounds
      if(interact(*floor->getCase(i,j-1))){
	floor->setBoard(i,j-1,this);
	setSymbole('<');
	floor->setBoard(i,j);
	setJ(j-1);
      }
    }
  }else if( c == 'o'){
    if(i > 0 && floor->getCase(i-1,j)->typeOf() != WALL){
      if(interact(*floor->getCase(i-1,j))){
	floor->setBoard(i-1,j,this);
	setSymbole('^');
	floor->setBoard(i,j);
	setI(i-1);
      }
    }
  }else if( c == 'l'){
    if(i < floor->getN()-1){
      if(interact(*floor->getCase(i+1,j))){
	floor->setBoard(i+1,j,this);
	setSymbole('v');
	floor->setBoard(i,j);
	setI(i+1);
      }
    }
  }else if(c == 'm'){
    if(j < floor->getM()-1){
      if(interact(*floor->getCase(i,j+1))){
	floor->setBoard(i,j+1,this);
	setSymbole('>');
	floor->setBoard(i,j);
	setJ(j+1);
      }
    }
  }
  setPlayed(true);
}

bool Player::interact(Case & c){
  if(c.typeOf() == EMPTY)
    return true;
  else if(c.typeOf() == SOURCE)
    return healSource();
  else if(c.typeOf() == ITEM)
    return false;
  else if(c.typeOf() == STAIRS_UP){
    game->getFloor(game->i_current_floor)->setBoard(getI(),getJ());
    game->setCurrentFloor((game->i_current_floor+1+game->getNbFloor())%game->getNbFloor());
    game->getFloor(game->i_current_floor)->setBoard(1,1,this);
    setFloor(game->getFloor(game->i_current_floor));
    setJ(1);
    setI(1);
    return false;
  }else if(c.typeOf() == STAIRS_DOWN){
    game->getFloor(game->i_current_floor)->setBoard(getI(),getJ());
    game->setCurrentFloor((game->i_current_floor-1+game->getNbFloor())%game->getNbFloor());
    game->getFloor(game->i_current_floor)->setBoard(1,1,this);
    setFloor(game->getFloor(game->i_current_floor));
    setJ(1);
    setI(1);
    return false;
  }else if(c.typeOf()==WEAPON){
    return askUseOrStore((Weapon&)c);
  }else if((c.typeOf()%10) == POTION){
    return askUseOrStore((Potion&)c);
  }else if(c.typeOf() == MONSTER){
    attack((People&)c);
    return false;
  }
}

bool Player::healSource(){
  life = MAX_LIFE_PLAYER;
  cout << BOLDGREEN << "Thanks to the source, you get full life ("
       <<life<<"hp"<<")"<<RESET<<endl;
  return false;
}

bool Player::askUseOrStore(Potion &potion){
  char answer = 0;
  bool b = true;
  char c;
  cout << "Do you want to use(u) " << potion.getName() <<
    " or store(s) it in your bag ? Or do nothing (n)" << endl;
  while(b){
    system("stty raw");
    c = getchar();
    system("stty cooked");
    cout << endl;
    if(c != 'u' && c != 's' && c != 'n')
      cout << RED << "Wrong answer. Press u to use " << potion.getName()
	   <<", s to store it or n to do nothing" << RESET << endl;
    else
      b = false;
  }
  if(c == 'n')
    return false;
  if(c == 's')
    Add_item_bag(potion);
  else
    use(potion);
  return true;
}

bool Player::askUseOrStore(Weapon &weapon){
  char answer = 0;
  bool b = true;
  char c;
  cout << "Do you want to use(u) " << weapon.getName() <<
    ",store(s) it in your bag or do nothing(n) ?" << endl;
  while(b){
    system("stty raw");
    c = getchar();
    system("stty cooked");
    cout << endl;
    if(c != 'u' && c != 's' && c!='n')
      cout << RED << "Wrong answer. Press u to use " << weapon.getName()
	   <<", s to store it or n to do nothing" << RESET << endl;
    else
      b = false;
  }
  if(c == 's'){
    Add_item_bag(weapon);
  }else if(c == 'n')
    return false;
  else
    if(weapon.typeOf()==WEAPON)
	setWeapon((Weapon &)weapon);
  return true;
}

int Player::typeOf() const{ return PLAYER; }

void Player::use(Potion &p){
  if(p.typeOf() == POSION){
    if(life - p.getEffect() <= 0)
      die();
    else
      life -= p.getEffect();
    cout << "Your drunk posion, not potion ... Now " << getName() << " have "
	 <<getLife()<<" hp" << endl;
  }else if(p.typeOf() == RESI_UP){
    resi += (double)p.getEffect();
    cout << "You drunk ResiUp, now your resi :"<<resi<<endl;
  }
  else if(p.typeOf() == RESI_DOWN){
    resi -= (double)p.getEffect();
    cout << "You drunk ResiDown, now your resi :"<<resi<<endl;
  }
  else if(p.typeOf() == HEALING){
    if(life + p.getEffect() > MAX_LIFE_PLAYER)
      life = MAX_LIFE_PLAYER;
    else
      life += p.getEffect();
    cout << "Healing Potion used. Now " << getName() << " has "
	 <<getLife()<<" hp" << endl;
  }
}
