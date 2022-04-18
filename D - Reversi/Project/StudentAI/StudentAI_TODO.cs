using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Pipes;
using FullSailAFI.GamePlaying.CoreAI;

namespace FullSailAFI.GamePlaying
{
    public class StudentAI : Behavior
    {
        TreeVisLib treeVisLib;  // lib functions to communicate with TreeVisualization
        bool visualizationFlag = false;  // turn this on to use tree visualization (which you will have to implement via the TreeVisLib API)
                                         // WARNING: Will hang program if the TreeVisualization project is not loaded!

        public StudentAI()
        {
            if (visualizationFlag == true)
            {
                if (treeVisLib == null)  // should always be null, but just in case
                    treeVisLib = TreeVisLib.getTreeVisLib();  // WARNING: Creation of this object will hang if the TreeVisualization project is not loaded!
            }
        }

        //
        // This function starts the look ahead process to find the best move
        // for this player color.
        //
        public ComputerMove Run(int _nextColor, Board _board, int _lookAheadDepth)
        {
            ComputerMove nextMove = GetBestMove(_nextColor, _board, _lookAheadDepth);
            return nextMove;
        }

        //
        // This function uses look ahead to evaluate all valid moves for a
        // given player color and returns the best move it can find. This
        // method will only be called if there is at least one valid move
        // for the player of the designated color.
        //
        private ComputerMove GetBestMove(int color, Board board, int depth)
        {
            //TODO: the lab
            //throw new NotImplementedException();
            ComputerMove bestMove = null;
            Board newState = new Board();
            List<ComputerMove> myMoves = new List<ComputerMove>();

            //generate valid Moves for player;
            for (int i = 0; i < 8; i++)// row
            {
                for (int j = 0; j < 8; j++) //column
                {
                    ComputerMove table = new ComputerMove(0, 0);
                    table.row = i;
                    table.col = j;
                    myMoves.Add(table);
                }
            }

            foreach (ComputerMove checkMoves in myMoves)
            {
                newState.Copy(board);
                if (newState.IsValidMove(color, checkMoves.row, checkMoves.col))
                {
                    newState.MakeMove(color, checkMoves.row, checkMoves.col);

                    if (newState.IsTerminalState() || depth == 0)
                    {
                        checkMoves.rank = Evaluate(newState);
                    }
                    else
                    {
                        if (newState.HasAnyValidMove(-color))
                        {  checkMoves.rank = Run(-color, newState, depth - 1).rank; }
                        else
                        { checkMoves.rank = Run(color, newState, depth - 1).rank; }

                        //checkMoves.rank = Run(GetNextPlayer(color, newState), newState, depth - 1).rank;
                    }
                    //checkMoves.rank = Evaluate(newState);
                    if (color == -1)
                    {
                        if (bestMove == null || checkMoves.rank < bestMove.rank)
                        { bestMove = checkMoves; }
                    }
                    else
                    {
                        if (bestMove == null || checkMoves.rank > bestMove.rank)
                        { bestMove = checkMoves; }
                    }
                }
            }
            return bestMove;
        }

        #region Recommended Helper Functions

        private int Evaluate(Board _board)
        {
            //TODO: determine score based on position of pieces
            //return ExampleAI.MinimaxAFI.EvaluateTest(_board); // TEST WITH THIS FIRST, THEN IMPLEMENT YOUR OWN EVALUATE
            //TODO: the lab
            //throw new NotImplementedException();

            //add the values
            int value = 0;

            for (int i = 0; i < 8; i++)// row
            {
                for (int j = 0; j < 8; j++) //column
                {
                    int color = _board.GetSquareContents(i, j);
                    if ((i == 0 && j == 0) || (i == 7 && j == 0) || (i == 0 && j == 7) || (i == 7 && j == 7))
                    { value += color * 100; }
                    else if (i == 0 || i == 7 || j == 0 || j == 7)
                    { value += color * 10; }
                    else
                    { value += color; }
                }
            }

            if (_board.IsTerminalState())
            {
               if (value > 0)
               { value += 1000; }
               else
               { value -= 1000; }
            }

            return value;
        }


        //private int GetNextPlayer(int player, Board gameState)
        //{
        //    if (gameState.HasAnyValidMove(-player))
        //        return -player;
        //    else
        //        return player;
        //}
        #endregion

    }
}
