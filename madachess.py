import pygame
import sys
import chess
import chess.engine
import threading
import socket
from madaLib import *
import pickle
import asyncio


def drawEval(board, info, screen, squareSize, moveNr):
    b = chess.Board(board.fen())
    r = pygame.Rect(squareSize * 8 + 10, 50 * moveNr + 50, 1000, 50)
    pygame.draw.rect(screen, bgColor, r)
    moves = ""
    for m in info.get("pv"):
        moves += b.san(m) + " "
        b.push(m)
    text_surface = FONT.render(moves, True, fgColor)  
    screen.blit(text_surface, (squareSize * 8 + 10, 50 * moveNr + 50))

    text_surface = FONT.render(str(info.get("score").white()) + " " + str(info.get("depth")), True, fgColor)
    screen.blit(text_surface, (squareSize * 8 + 10, 20 + 50 * moveNr + 50))

class doEval:
    def __init__(self, screen):
        self.screen = screen
        self.squareSize = 0
        self.running = True
        self.multipv = 4

    def think(self, board):
        with sf.analysis(board, chess.engine.Limit(depth=200), multipv=self.multipv) as analysis:
            for info in analysis:
                if (info.get("pv")):
                    drawEval(board, info, self.screen, self.squareSize, info.get("multipv"))

                if not self.running or info.get("seldepth", 0) > 200:
                    break

def main(screen, host_ip, server_port):
    pickle_off = open ("games", "rb")
    games = pickle.load(pickle_off)
    updated = 1
    cBoard = 0
    t1 = None
    board = chess.Board("nrbkrbnq/pppppppp/8/8/8/8/PPPPPPPP/NRBKRBNQ w EBeb - 0 1", chess960=True)
    #board = chess.Board() 
    clicked = None
    hoveringPiece = None
    evalObj = doEval(screen)
    sizeX, sizeY = screen.get_size()
    doEngine = True
    while True:
        sizeOld = [sizeX, sizeY]
        sizeX, sizeY = screen.get_size()
        squareSize = sizeX // 8 if sizeX < sizeY else sizeY // 8
        evalObj.squareSize = squareSize
        boardRect = pygame.Rect(0, 0, squareSize * 8, squareSize * 8)
        if [sizeX, sizeY] != sizeOld or updated:
            updated = 0
            #pygame.draw.rect(screen, bgColor, pygame.Rect(0, 0, sizeX, sizeY))
            drawBoard(screen, board, squareSize, clicked)

        events = pygame.event.get()
        for event in events:
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    try:
                        board.pop()
                        if t1:
                            evalObj.running = False
                            t1.join()
                            evalObj.board = board
                            evalObj.running = True
                        drawBoard(screen, board, squareSize, clicked)

                        t1 = threading.Thread(target=evalObj.think, args=(board,))
                        t1.start()
                    except Exception:
                        pass

                if event.key == pygame.K_e:
                    if evalObj.running:
                        evalObj.running = False
                        print("Stopped eval")
                    else:
                        evalObj.running = True
                        t1 = threading.Thread(target=evalObj.think, args=(board,))
                        t1.start()
                        print("Started eval")

                if event.key == pygame.K_c:
                    i = input("enter command\n")
                    if i == "eval off":
                        evalObj.running = false
                        doEngine = false
                if event.key == pygame.K_n:
                    games.append([board, input("Give a name to the Board:\n")])
                    with open("games", "wb") as data:
                        pickle.dump(games, data)
                    print("Game %s saved"%(games[-1][1]))
                if event.key == pygame.K_m:
                    evalObj.multipv = int(input("Set number multipv lines:\n"))
                    updated = 1
                    pygame.draw.rect(screen, bgColor, pygame.Rect(0, 0, sizeX, sizeY))
                if event.key == pygame.K_s:
                    with open("games", "wb") as data:
                        pickle.dump(games, data)
                    print("Saved all games")
                if event.key == pygame.K_l:
                    with open("games", "wb") as data:
                        pickle.dump(games, data)
                    print("Saved all games")
                    pickle_off = open ("games", "rb")
                    games = pickle.load(pickle_off)
                    for i in range(1, len(games)):
                        print("(%d) %s"%(i, games[i][1]))
                    cBoard = int(input("which game to load?\n"))
                    board = games[cBoard][0]
                    updated = 1
                    print("Loaded game %s"%(games[cBoard][1]))


            if event.type == pygame.MOUSEBUTTONDOWN:
                left, middle, right = pygame.mouse.get_pressed()
                x, y = pygame.mouse.get_pos()
                if boardRect.collidepoint((x, y)):
                    clicked = x // squareSize + (7 - y // squareSize) * 8
                    hoveringPiece = board.piece_at(clicked)
                    updated = 1
            if event.type == pygame.MOUSEBUTTONUP and clicked != None:
                x, y = pygame.mouse.get_pos()
                newSquare = x // squareSize + (7 - y // squareSize) * 8
                move = chess.Move(clicked, newSquare)
                if move in board.legal_moves:
                    if t1:
                        evalObj.running = False
                        t1.join()
                        evalObj.board = board
                        evalObj.running = True
                    board.push(move)

                    t1 = threading.Thread(target=evalObj.think, args=(board,))
                    t1.start()
                else:
                    move = chess.Move(clicked, newSquare, promotion=5)
                    print(move)
                    if move in board.legal_moves:
                        if t1:
                            evalObj.running = False
                            t1.join()
                            evalObj.board = board
                            evalObj.running = True
                        board.push(move)
    
                        t1 = threading.Thread(target=evalObj.think, args=(board,))
                        t1.start()

                hoveringPiece = None
                clicked = None
                drawBoard(screen, board, squareSize, clicked)
                updated = 1
        if hoveringPiece != None:
            drawHoveringPiece(screen, squareSize, pygame.mouse.get_pos(), hoveringPiece)
            updated = 1


        pygame.display.update()

pygame.init()
screen = pygame.display.set_mode((100, 100), pygame.RESIZABLE)
screen.fill(bgColor)
main(screen, None, None)
pygame.quit()
sys.exit()
