function retryForever(fn) {
  try {
    var val = fn();
    if(val == true) {
      $('#loading').slideUp();
      $('#solveButton').show();
      return;
    }
  } catch (err) {
    console.log(err);
    console.log('retry...');
    return retryForever(fn);
  }
}

function tryGeneratingBoard() {
  // size = {4, 9, 16}
  // difficulty = {"easy", "medium", "hard", "very hard"}
  var size = 16;
  var mySudokuJS = $("#sudoku").sudokuJS({
    boardSize: size,
    difficulty: "very hard"
  });

  $('#solve').on('click', function() {
    var board = mySudokuJS.getBoard();
    var arrayBoard = board.map(function(obj) {
      return obj.val;
    });

    for(i = 0; i < arrayBoard.length; i++) {
      if(arrayBoard[i] == null) {
        arrayBoard[i] = 0;
      }
    }

    mySudokuJS.solveAll();
    console.log(arrayBoard);
    console.log(arrayBoard.join(" "));
    console.log(mySudokuJS);
  });
  return true;
}

// add ability to select board size. currently hard coded
//console.log(a);
retryForever(tryGeneratingBoard)
