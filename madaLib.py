import pygame
import sys
import chess
import chess.engine

# Define some constants for the color values
bgColor = "#1B1D1E"
fgColor = "#F8F8F2"
CR = "#CC241D"
sf = chess.engine.SimpleEngine.popen_uci(r"/usr/bin/stockfish")
config = {"Threads": 4, "Hash": 2048}
sf.configure(config)
newMove = False


# Define some constants for the chess piece names and their corresponding images
PIECES = {
    "P": "P.png",
    "N": "N.png",
    "B": "B.png",
    "R": "R.png",
    "Q": "Q.png",
    "K": "K.png",
    "p": "p.png",
    "n": "n.png",
    "b": "b.png",
    "r": "r.png",
    "q": "q.png",
    "k": "k.png"
}

# Create a dictionary to store the images of the pieces
piecesImg = {piece: pygame.image.load("pieces/" + filename) for piece, filename in PIECES.items()}

# Initialize the Pygame font module
pygame.font.init()

# Create a font object
FONT = pygame.font.SysFont("JetBrains Mono Medium", 20)

def drawBoard(screen, board, squareSize, clicked):
    """Draws the chess board and pieces on the screen.

    Args:
        screen: the Pygame surface to draw the board on
        board: the chess.Board object representing the current game state
        squareSize: the size of each square on the board
    """
    for x in range(8):
        for y in range(8):
            # Create a rectangle for the current square
            rect = pygame.Rect(x * squareSize, (7 - y) * squareSize, squareSize, squareSize)
            # Fill the rectangle with the appropriate color
            color = fgColor if (x + y) % 2 == 1 else bgColor
            pygame.draw.rect(screen, color, rect)

            # Get the chess piece at the current square, if any
            piece = board.piece_at(8 * y + x)
            if piece and clicked != x + y * 8:
                drawPiece(screen, piece, x, y, squareSize)

def drawPiece(screen, piece, x, y, squareSize):
    # Get the corresponding image for the piece
    img = piecesImg[piece.symbol()]
    # Scale the image to the appropriate size
    img = pygame.transform.scale(img, (squareSize, squareSize))
    # Draw the image on the square
    screen.blit(img, (x * squareSize, (7 - y) * squareSize))

def drawHoveringPiece(screen, squareSize, pos, hoveringPiece):
    if hoveringPiece == None:
        return
    img = piecesImg[hoveringPiece.symbol()]
    img = pygame.transform.scale(img, (squareSize, squareSize))
    # Draw the image on the square
    rect = pygame.Rect(0, 0, squareSize, squareSize)
    rect.center = pos
    screen.blit(img, rect)
