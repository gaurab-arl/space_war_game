// ---------------------------- collision.h ----------------------------
#ifndef COLLISION_H
#define COLLISION_H

#include "gameui.h"
#include "userui.h"

void check_collision_ship(Enemy &enemy);
void check_sky_bullets(Bullet &bullet);
void health_dead();
void user_bullets_fire(Bullet bullets[], Enemy enemies[], User &current_user);
void score_increase(User &current_user);

#endif // COLLISION_H
