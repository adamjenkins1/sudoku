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
  error = false;
  errorMsg = "\n";
  if(!(size == 4 || size == 9 || size == 16)) {
    error = true;
    errorMsg += "Invalid board size: " + size + ". Defaulting to size 9.\n";
    size = 9;
  }

  if(!(diff == "easy" || diff == "medium" || diff == "hard" 
        || diff == "very hard")) {
    error = true;
    errorMsg += "Invalid difficulty: " + diff + ". Defaulting to medium.\n";
    diff = "medium";
    shortDiff = "m";
  }

  if(error == true) {
    alert(errorMsg);
    $(location).attr('href', '/' + size + '/' + shortDiff + '/'); 
    return;
  }

  var mySudokuJS = $("#sudoku").sudokuJS({
    boardSize: size,
    difficulty: diff
  });

  $('#solve').on('click', function() {
    var board = mySudokuJS.getBoard();
    var arrayBoard = board.map(function(obj) {
      return obj.val;
    });

    solved = true;
    for(i = 0; i < arrayBoard.length; i++) {
      if(arrayBoard[i] == null) {
        solved = false;
        arrayBoard[i] = 0;
      }
    }


    if(solved == true) {
      alert('Board already solved, no need to solve it again!');
    }
    else {
      $.post("/solve/", {board: arrayBoard}, function(result) {
        console.log(result);
        mySudokuJS.setBoard(result);
      });
      //mySudokuJS.solveAll();
      console.log(arrayBoard);
      console.log(arrayBoard.join(" "));
      console.log(mySudokuJS);
    }
  });
  return true;
}

function csrfSafeMethod(method) {
  return (/^(GET|HEAD|OPTIONS|TRACE)$/.test(method));
}

$.ajaxSetup({
  beforeSend: function(xhr, settings) {
    if (!csrfSafeMethod(settings.type) && !this.crossDomain) {
      xhr.setRequestHeader("X-CSRFToken", csrftoken);
    }
  }
});
retryForever(tryGeneratingBoard)
