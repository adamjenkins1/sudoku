function retryForever(fn) {
  try {
    var val = fn();
    if(val == true) {
      $('#loading').slideUp();
      $('#solveButton').show();
      return;
    }
  } 
  catch (err) {
    console.log(err);
    console.log('retry...');
    return retryForever(fn);
  }
}

function tryGeneratingBoard() {
  // size = {4, 9, 16}
  // difficulty = {'easy', 'medium', 'hard', 'very hard'}
  var error = false;
  var errorMsg = '\n';
  var solveClicked = false;
  if(!(size == 4 || size == 9 || size == 16)) {
    error = true;
    errorMsg += 'Invalid board size: ' + size + '. Defaulting to size 9.\n';
    size = 9;
  }

  if(!(diff == 'easy' || diff == 'medium' || diff == 'hard' 
        || diff == 'very hard')) {
    error = true;
    errorMsg += 'Invalid difficulty: ' + diff + '. Defaulting to medium.\n';
    diff = 'medium';
    shortDiff = 'm';
  }

  if(!(algorithm == 'AC3' || algorithm == 'Genetic' || algorithm == 'Hill')) {
    error = true;
    errorMsg += 'Invalid algorithm: ' + algorithm + '. Defaulting to AC3.\n';
    algorithm = 'AC3';
  }

  if(error == true) {
    alert(errorMsg);
    $(location).attr('href', '/' + size + '/' + shortDiff + '/' + algorithm + '/'); 
    return;
  }

  var mySudokuJS = $('#sudoku').sudokuJS({
    boardSize: size,
    difficulty: diff
  });

  $('#solve').on('click', function() {
    if(solveClicked == false) {
      solveClicked = true;
      var board = mySudokuJS.getBoard();
      var arrayBoard = board.map(function(obj) {
        return obj.val;
      });

      $('#refresh').on('click', function() {
        $(location).attr('href', '/' + size + '/' + shortDiff + '/' + algorithm + '/'); 
        return;
      });

      for(i = 0; i < arrayBoard.length; i++) {
        if(arrayBoard[i] == null) {
          arrayBoard[i] = 0;
        }
      }

      var url = '/solve/' + algorithm + '/' + shortDiff + '/';
      $.post(url, {board: arrayBoard})
        .done(function(result) {
          console.log(arrayBoard);
          console.log(result);
          mySudokuJS.setBoard(result);
          $('#refreshButton').show();
          $('#solveButton').hide();
        })
      .fail(function(xhr, status, error) {
        if(xhr.status == 400) {
          mySudokuJS.setBoard(xhr.responseJSON);
          msg = '';
          if(algorithm == 'Hill') {
            msg = 'Error: solver unable to find solution using hill climbing algorithm.';
          }
          else if(algorithm == 'AC3' || algorithm == 'Genetic') {
            msg = 'Error: solver unable to find solution using ' + algorithm + ' algorithm.';
          }
          alert(msg);
          $('#refreshButton').show();
          $('#solveButton').hide();
        }
      });
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
      xhr.setRequestHeader('X-CSRFToken', csrftoken);
    }
  }
});
retryForever(tryGeneratingBoard)
