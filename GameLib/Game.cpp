#include "Game.h"

Game::Game()
{

}//Game::Game()


int Game::Initialize()
{
    //�X�R�A�̏�����
    _score = 0;
    _highScore = 0;
    //�V�[���̑��
    _scenes[TITLE_SCENE] = new TitleScene();
    _scenes[READY_SCENE] = new ReadyScene();
    _scenes[MAIN_SCENE]  = new MainScene();

    //�V�[����S�ď�����
    for (int i = 0; i < MAX_SCENE; i++)
    {
        _scenes[i]->Initialize();
    }//for (int i = 0; i < MAX_SCENE; i++)

     //�V�[���̃��[�h
    _sceneOfIndex = TITLE_SCENE;
    _currentScene = _scenes[_sceneOfIndex];
   

    return 0;
}//int Game::Initialize()

void Game::Update()
{
    //�Q�[�����N���A�����Ƃ��̏���
    if (gInvaderEx._count <= 0)
    {
        //�C���x�[�_�����ׂē|����AShip�̎c�@���c���Ă�����N���A
        if ((Invader::GetCountAlives() <= 0) && gShip.GetRemaningLives() <= 0) 
        {
            //���̃X�e�[�W�֐ݒ肷��
            _currentStage++;
            //�X�e�[�W�����Z�b�g����
            ResetStage();
        }
    }// if (gInvaderEx._count <= 0)
}//void Game::Update()


void Game::Draw()
{
}//void Game::Draw()


void Game::DrawScore()
{
    vec2 size = vec2(5, DEFAULT_GAME_HEIGHT);
    Text2D(4 * DEFAULT_GAME_HEIGHT, DEFAULT_GAME_HEIGHT * 2, size, "%04d", gGame.GetScore());
}//void Game::DrawScore()


void Game::AddScore(int score)
{
    _score += score;
    //�X�R�A���ő�ɂȂ������̏���
    if (_score > MAX_SCORE)
    {
        _score = MAX_SCORE;
    }//if (_score >> MAX_SCORE)

    //�n�C�X�R�A�̍X�V
    if (_score > _highScore)
    {
        _highScore = _score;
    }//if (_score > _highScore)

}//void Game::AddScore()

void Game::ResetStage()
{
    //Ship�̃��Z�b�g
    gShip.Reset();
    //�C���x�[�_�[�̃��Z�b�g
    Invader::AllReset();
    //Torchka�̃��Z�b�g
    for (int i = 0;i < MAX_TORCHKA; i++)
    {
        gTorchka[i].Reset();
    }//for (int i = 0;i < MAX_TORCHKA; i++)
    //Ufo�̃��Z�b�g
    gUfo.Reset();

}//void Game::ResetStage()


void Game::SetScene(int scene)
{
    //�V�[���̃��[�h
    //_sceneOfIndex = READY_SCENE;
    _sceneOfIndex = scene;
    _currentScene = _scenes[_sceneOfIndex];
    //���̃V�[���ɐ؂�ւ����烊�Z�b�g����
    _currentScene->Reset();

}//void Game::SetScene(int scene)


bool Game::isGameOver()
{
    //printf("isGameOver���Ăяo���ꂽ\n");
    //Ship�̎c�@���Ȃ��Ȃ�����true��Ԃ�
    if ((gShip.GetRemaningLives() <= 0))
    {
        return true;
    }//if ((gShip.GetRemaningLives() <= 0))

    //�C���x�[�_�[��Torchka�𒴂�����Q�[���I�[�o�[
    //�S�ẴC���x�[�_�[���`�F�b�N����
    for (int i = 0; i < MAX_INVADER_ROW; i++)
    {
        for (int j = 0; j < MAX_INVADER_COLUMN; j++)
        {
            //torchka�𒴂��������肷��
            if (gInvaders[i][j].GetPosition().y >= SHIP_DEFAULT_Y)
            {
                return true;
            }
        }//for (int j = 0; j < MAX_INVADER; j++)
    }//for (int i = 0; i < MAX_INVADER; i++)

    return false;
}//bool Game::isGameOver()





