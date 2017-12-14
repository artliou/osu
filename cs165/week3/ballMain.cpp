#include "Player.hpp"
#include "Team.hpp"

int main()
{
  Player p1("Charlotte", 24, 10, 7);
  Player p2("Emily", 21, 13, 9);
  Player p3("Anne", 20, 10, 8);
  Player p4("Jane", 19, 10, 10);
  Player p5("Mary", 18, 11, 8);
  p5.setRebounds(12);

  Team team1(p1, p2, p3, p4, p5);

  Player p = team1.getShootingGuard();
  cout << p.getName() << endl;
}
