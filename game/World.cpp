#include "World.hpp"

template <typename T>
std::string toString(const T& value)
{
    std::stringstream stream;
    stream << value;
    return stream.str();
}

int result = 0;

Context::Context(TextureManager& textureManager, std::vector<Bullet*>& bulletList, std::vector<Meteor*>& meteorList)
: mTextureManager(&textureManager)
, mBulletList(&bulletList)
, mMeteorList(&meteorList)
{

}

World::World()
: mTextureManager()
, mBulletList()
, mMeteorList()
, mContext(mTextureManager, mBulletList, mMeteorList)
, mPlayerList()
, mStarsList()
, mFont()
, mText()
, hasWin(false)
{
    srand(time(NULL));

    mFont.loadFromFile("Media/Fonts/STENCIL.TTF");
    mText.setFont(mFont);
    mText.setCharacterSize(72);


    mMainTime.openFromFile("Media/Audio/sound_battle.ogg");
    mMainTime.setVolume(50.f);
    mMainTime.setLoop(true);
    mMainTime.play();


    mWinTime.openFromFile("Media/Audio/sound_finish.ogg");
    mWinTime.setVolume(50.f);
    mWinTime.setLoop(true);


    mText.setColor(sf::Color::Red);
    mText.setString("");
    mText.setOrigin(mText.getLocalBounds().width/2,mText.getLocalBounds().top/2);
    mText.setPosition(WIDTH/2, HEIGHT /2 - mText.getLocalBounds().top/2 - 20);


    mTextureManager.loadTexture(TextureID::PlayerTexture, "Media/Texture/Saak'ak.png");
    mTextureManager.loadTexture(TextureID::StarsTexture, "Media/Texture/stars.png");

    for(size_t i = 0; i < 40; ++i)
        mStarsList.push_back(new Stars(rand() % WIDTH, rand() % HEIGHT ,0,4,4,0, rand() % 3,rand() % 100));

    for(auto i : mStarsList)
        i->createAnimations(mTextureManager);

    for (unsigned int i = 0; (i < sf::Joystick::Count) && (mPlayerList.size() < mMaxPlayers); ++i)
    {
        if(sf::Joystick::isConnected(i))
        {
            for(size_t j = 0; j < 4; ++j)
            {
                if(playersData[j].isLocked == false)
                {
                    playersData[j].isLocked = true;
                    playersData[j].pos = mPlayerList.size();

                    Player* player = new Player(i,mContext, playersData[j].x,
                                                playersData[j].y, 300.f,
                                                playersData[j].angle, 64,64);
                    player->createAnimations(mTextureManager);
                    mPlayerList.push_back(player);
                    break;
                }
            }
        }
    }


    mMeteorList.push_back(new Meteor(64/2,                          HEIGHT /2,                      0,0, 64, 64));
    mMeteorList.push_back(new Meteor(WIDTH/2,                           64 /2,                      0,0, 64, 64));

    mMeteorList.push_back(new Meteor(WIDTH - 64/2,                  HEIGHT /2,                      0,0, 64, 64));
    mMeteorList.push_back(new Meteor(WIDTH/2,                       HEIGHT - 64 /2,                 0,0, 64, 64));


    mMeteorList.push_back(new Meteor(WIDTH/2,                       HEIGHT /2,                      0,0, 64, 64));
    mMeteorList.push_back(new Meteor(WIDTH/2 / 2,                   HEIGHT / 2 / 2,                 0,0, 64, 64));
    mMeteorList.push_back(new Meteor((WIDTH/2 / 2) + (WIDTH/2),     (HEIGHT / 2 / 2)+ (HEIGHT / 2), 0,0, 64, 64));
    mMeteorList.push_back(new Meteor((WIDTH/2 / 2),                 (HEIGHT / 2 / 2)+ (HEIGHT / 2), 0,0, 64, 64));
    mMeteorList.push_back(new Meteor((WIDTH/2 / 2) + (WIDTH/2),     (HEIGHT / 2 / 2),               0,0, 64, 64));

    for(auto i : mMeteorList)
        i->createAnimations(mTextureManager);
}

void World::handleEvents(const sf::Event event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Space)
        {
            if(hasWin)
            {
                hasWin = false;

                mMainTime.play();
                mWinTime.stop();
                for(size_t j = 0; j < 4; ++j)
                {
                    playersData[j].result = 0;
                }
                mText.setString("");
            }
        }
    case sf::Event::JoystickMoved:
        if(!hasWin)
        for(auto i : mPlayerList)
            i->handleEvents();
        break;
    case sf::Event::JoystickButtonPressed:
        if(!hasWin)
        for(auto i : mPlayerList)
            i->handleEvents();
        break;
    case sf::Event::JoystickButtonReleased:
        if(!hasWin)
        for(auto i : mPlayerList)
            i->handleEvents();
        break;
    case sf::Event::JoystickConnected:

        if(!hasWin)
        {
            printf("Hello %i: ",event.joystickConnect.joystickId);

            if(mPlayerList.size() < mMaxPlayers)
            {
                for(size_t j = 0; j < 4; ++j)
                {
                    if(playersData[j].isLocked == false)
                    {
                        playersData[j].isLocked = true;
                        playersData[j].pos = mPlayerList.size();

                        Player* player = new Player(event.joystickConnect.joystickId,mContext, playersData[j].x,
                                                    playersData[j].y, 300.f,
                                                    playersData[j].angle, 64,64);
                        player->createAnimations(mTextureManager);
                        mPlayerList.push_back(player);
                        break;
                    }
                }
            }

            for(size_t j = 0; j < 4; ++j)
            {
                printf("% i", playersData[j].isLocked);
            }
            printf("\n");
        }

        break;
    case sf::Event::JoystickDisconnected:
        if(!hasWin)
        {
            printf("By by %i :",event.joystickConnect.joystickId);
            for(size_t i = 0; i <  mPlayerList.size(); ++i)
            {
                if(mPlayerList[i]->getNumber() == event.joystickConnect.joystickId)
                {
                    delete mPlayerList[i];
                    mPlayerList.begin() + i = mPlayerList.erase(mPlayerList.begin() + i);

                    for(size_t j = 0; j < 4; ++j)
                    {
                        if(playersData[j].pos == i)
                        {
                            playersData[j].isLocked = false;
                            playersData[j].pos = -1;
                            playersData[j].result = 0;
                            break;
                        }
                    }
                    break;
                }
            }

            for(size_t j = 0; j < 4; ++j)
            {
                printf("% i", playersData[j].isLocked);
            }

            printf("\n");
        }
        break;
    default:
        break;
    }
}

void World::update(float time)
{
    if(!hasWin)
    {
        for(size_t j = 0; j < 4; ++j)
        {
            if(playersData[j].result >= mMaxKILL)
            {
                printf("PLAYER %i WIN!\n", j + 1);

                std::string tempStr;

                switch (mPlayerList[playersData[j].pos]->getNumber())
                {
                case 0:
                    mText.setColor(sf::Color::Blue);
                     tempStr = "PLAYER BLUE WIN!";
                    break;
                case 1:
                    mText.setColor(sf::Color::Green);
                    tempStr = "PLAYER GREEN WIN!";
                    break;
                case 2:
                    mText.setColor(sf::Color::Red);
                    tempStr = "PLAYER RED WIN!";
                    break;
                case 3:
                    mText.setColor(sf::Color::Yellow);
                    tempStr = "PLAYER YELLOW WIN!";
                    break;
                default:
                    break;
                }

                mText.setString(tempStr);
                mText.setOrigin(mText.getLocalBounds().width / 2,mText.getLocalBounds().top /2);
                mText.setPosition(WIDTH/2,  HEIGHT /2 - mText.getLocalBounds().top/2 - 20);

                hasWin = true;
                mMainTime.stop();
                mWinTime.play();
                break;
            }
        }

        for(auto i : mPlayerList)   i->update(time);
        for(auto i : mStarsList)    i->update(time);
        for(auto i : mBulletList)   i->update(time);
        for(auto i : mMeteorList)   i->update(time);

        //столкновение игрока с метиорами
        for(auto j : mPlayerList)
            for(auto i : mMeteorList)
                if(j->getBody().intersects(i->getBody()))
                {
                    int angle = j->getBody().getAngle(i->getBody());
                    float distance = j->getBody().radius + i->getBody().radius;
                    j->getBody().x = i->getBody().x + distance * (sin(angle / (180 / M_PI)));
                    j->getBody().y = i->getBody().y + distance * (cos(angle / (180 / M_PI))) * -1;

                    angle += 180;
                    angle %= 360;
                    i->setFlightAngle(angle);
                    i->setSpeed(j->getSpeed() / 5);
                }

        //столкновение пулей с игроком
        for(auto j : mPlayerList)
            for(auto i : mBulletList)
                if(j->isAlive() && i->isAlive())
                {
                    if (j->getBody().intersects(i->getBody()))
                    {
                        for(size_t k = 0; k < mPlayerList.size(); ++k)
                        {
                            if(mPlayerList[k]->getNumber() == i->getNumPlayer())
                            {
                                if(!j->hasShield())
                                {
                                    if(j->getNumber() == mPlayerList[k]->getNumber())
                                        playersData[k].result--;
                                    else
                                        playersData[k].result++;
                                }
                                break;
                            }
                        }

                        if(!j->hasShield())
                            j->die();

                        i->die();
                    }
                }

        //Коллозия между игроками, если не сохранить в tX и tY , то 1 всегда будет толкать а другой нет!
        if(mPlayerList.size() > 1)
        {
            for(auto i : mPlayerList)
                for(auto j : mPlayerList)
                    if(i != j)
                    {
                        if(j->getBody().intersects(i->getBody()))
                        {
                            int angle = j->getBody().getAngle(i->getBody());
                            float distance = j->getBody().radius + i->getBody().radius;

                            float tX = j->getBody().x;
                            float tY = j->getBody().y;

                            if(j->isAlive())
                            {
                                j->getBody().x = i->getBody().x + distance * (sin(angle / (180 / M_PI)));
                                j->getBody().y = i->getBody().y + distance * (cos(angle / (180 / M_PI))) * -1;
                            }

                            angle += 180;
                            angle %= 360;
                            if(j->isAlive())
                            {
                                i->getBody().x = tX + distance * (sin(angle / (180 / M_PI)));
                                i->getBody().y = tY + distance * (cos(angle / (180 / M_PI))) * -1;
                            }
                        }
                    }
        }

        //  столкновение метеоров с метеорами
        for(auto i : mMeteorList)
            for(auto j : mMeteorList)
                if(i != j)
                {
                    if(i->getBody().intersects(j->getBody()))
                    {
                        int angle = i->getBody().getAngle(j->getBody());
                        float distance = i->getBody().radius + j->getBody().radius;
                        i->getBody().x = j->getBody().x + distance * (sin(angle / (180 / M_PI)));
                        i->getBody().y = j->getBody().y + distance * (cos(angle / (180 / M_PI))) * -1;

                        angle += 180;
                        angle %= 360;
                        j->setFlightAngle(angle);
                        j->setSpeed(i->getSpeed() / 5);
                    }
                }

        //  столкновение пулей  с пулями
        for(auto i : mBulletList)
            for(auto j : mBulletList)
                if(i != j)
                {
                    if(i->getBody().intersects(j->getBody()))
                    {
                        i->die();
                        j->die();
                    }
                }

        //столкновение пулей с метеорами
        for(auto i : mBulletList)
            for(auto j : mMeteorList)
            {
                if(i->isAlive())
                    if (i->getBody().intersects(j->getBody()))
                    {
                        int angle = i->getBody().getAngle(j->getBody());
                        i->reduceStability();

                        Bullet& first = (*i);
                        Meteor& second = (*j);

                        double xDist = first.getBody().x - second.getBody().x;
                        double yDist = first.getBody().y - second.getBody().y;
                        double distSquared = xDist * xDist + yDist * yDist;

                        double xVelocity = second.getDSpeed().x - first.getDSpeed().x;
                        double yVelocity = second.getDSpeed().y - first.getDSpeed().y;
                        double dotProduct = xDist * xVelocity + yDist * yVelocity;
                        //Neat vector maths, used for checking if the objects moves towards one another.
                        if(dotProduct > 0)
                        {
                            double collisionScale = dotProduct / distSquared;
                            double xCollision = xDist * collisionScale;
                            double yCollision = yDist * collisionScale;
                            //The Collision vector is the speed difference projected on the Dist vector,
                            //thus it is the component of the speed difference needed for the collision.

                            double combinedMass = first.getBody().radius + second.getBody().radius;
                            double collisionWeightA = 2 * second.getBody().radius / combinedMass;
                            double collisionWeightB = 2 * first.getBody().radius / combinedMass;


                            double newVelX1 = first.getDSpeed().x;
                            double newVelY1 = first.getDSpeed().y;
                            double newVelX2 = second.getDSpeed().x;
                            double newVelY2 = second.getDSpeed().y;

                            newVelX1 += collisionWeightA * xCollision;
                            newVelY1 += collisionWeightA * yCollision;
                            newVelX2 -= collisionWeightB * xCollision;
                            newVelY2 -= collisionWeightB * yCollision;

                            first.setDSpeed(newVelX1, newVelY1);
                        }

                        angle += 180;
                        angle %= 360;
                        j->setFlightAngle(angle);
                        j->setSpeed(i->getSpeed());
                    }
            }

         //удаление мёртвых пулей
        for(auto i = mBulletList.begin(); i != mBulletList.end(); )
        {
            Bullet* bullet = *i;
            if(!bullet->isAlive() && !bullet->isPlaying())
            {

                delete *i;
                i = mBulletList.erase(i);
            }
            else
                i++;
        }

        //удаление звёзд
        for(auto i = mStarsList.begin(); i != mStarsList.end(); )
        {
            Stars* star = *i;
            if(!star->isAlive() && !star->isPlaying())
            {
                delete star;
                i = mStarsList.erase(i);
            }
            else
                i++;
        }

        //создание звезд
        unsigned int tempCountStars = rand() % 50;
        while(mStarsList.size() < tempCountStars)
        {
            Stars* star = new Stars(rand() % WIDTH, rand() % HEIGHT ,0,4,4,0, rand() % 3,rand() % 1000);
                star->createAnimations(mTextureManager);

            mStarsList.push_back(star);
        }
    }
}

void World::draw(sf::RenderWindow& window)
{
    for(auto i : mStarsList)    i->draw(window);
    for(auto i : mPlayerList)   i->draw(window);
    for(auto i : mBulletList)   i->draw(window);
    for(auto i : mMeteorList)   i->draw(window);

    window.draw(mText);
}
