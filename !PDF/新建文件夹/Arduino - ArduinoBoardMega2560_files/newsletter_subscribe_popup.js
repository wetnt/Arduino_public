$(document).ready(function() {
    
    function validateEmail(email) { 
        var re = /^(([^<>()[\]\\.,;:\s@\"]+(\.[^<>()[\]\\.,;:\s@\"]+)*)|(\".+\"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/;
        return re.test(email);
    } 

    var openPopup = function() {

      $('.confirm-popup').hide();
      $('.form-popup').show();

      var modalBody = $('#newsletterModalBody');
      var emailInput = modalBody.find('#newsletterEmailField').find('input');
      var subscribeButton = $('#subscribe-submit-btn');
      var emailMissingP = modalBody.find('#emailMissing');
      var formValid = false;
      var confirmHtml = $('#newsletterModalConfirm').html();
      var email = $('#sendy-EMAIL').val(); 

      //reset popup values / appearance
      $("#newsletterSubscribeStatus").hide();
      $('#newsletterModal').find('.modal-header-main').show();
      $('#newsletterModal').find('.modal-header-alt').hide();
      emailMissingP.hide();
      emailInput.val('');
      modalBody.find('#store').prop('checked', true);
      modalBody.find('#worldwide').prop('checked', true);

      //both checkboxes checked at beginning 
       
      subscribeButton.removeAttr('disabled');

      //If user didn't provide email by footer input box, show input box in the popup, else just checkboxes
      if(validateEmail(email)) {
        emailInput.val(email); 
        formValid = true;
      } else {
        emailMissingP.show();  
        subscribeButton.attr('disabled', 'disabled');
        $('#sendy-EMAIL').val('');
        formValid = false;
      }

      $('#newsletterModal').foundation('reveal', 'open');

      emailInput.on('input propertychange paste', function(e) {
           if(!validateEmail(emailInput.val())) {
              emailMissingP.show();
              subscribeButton.attr('disabled', 'disabled');
              formValid = false;
           } else {
              formValid = true;
              emailMissingP.hide();
              subscribeButton.removeAttr('disabled');
           }     
      });
    };

    $('#sendy-EMAIL').on('keypress', function(e) {
      if(e.keyCode == 13) {
        openPopup();
      }
    });

    $('#sendy-subscribe').on('click', function() {
      openPopup();
    });
  
    $("#sendy-subscribe-form").on('keypress', function(e) {
        if(e.keyCode == 13 && formValid) {
          e.preventDefault(); 
          $(this).submit();
        }
    });

    $('#subscribe-submit-btn').on('click', function(e){
      e.preventDefault(); 
      // disable 'NEXT' button to avoid multiple submits
      $('#subscribe-submit-btn').attr('disabled', 'disabled');
      $("#sendy-subscribe-form").submit();
    });

    $('#close-confirm-popup').on('click', function(e){
      $('#newsletterModal').foundation('reveal', 'close');  
    });

    // trigger click on checkbox when clicking text label
    $('.newsletter-form-label').on('click', function(e){
      $(this).siblings("label").click();
    });

    $("#sendy-subscribe-form").on('submit', function(e){
      e.preventDefault(); 
      
      var $form = $(this),
      //name = $form.find('input[name="name"]').val(),
      email = $form.find('input[name="email"]').val(),
      lists = $form.find('input[name="list[]"]:checked'),
      url = $form.attr('action');
      
      //reset
      $("#newsletterSubscribeStatus").hide(); 

      if(!lists.length) {
        $("#newsletterSubscribeStatus").html("Please select at least <br> one newsletter.");
        $("#newsletterSubscribeStatus").show(); 
        //button 'NEXT' can be enabled
        $('#subscribe-submit-btn').removeAttr('disabled');
        return;
      }

      var listValues = [];
      for(var i=0; i<lists.length; i++) {
        listValues.push($(lists[i]).val());
      }

      $.post(url, {lists:listValues, email:email},
        function(data) {
            if(data)
            {
              if(data=="All fields are required.")
              {
                $("#newsletterSubscribeStatus").text("Please fill in your email.");
                $("#newsletterSubscribeStatus").show(); 
              }
              else if(data=="Invalid email address.")
              {
                $("#newsletterSubscribeStatus").text("Your email address is invalid.");
                $("#newsletterSubscribeStatus").show(); 
              }
              // else if(data=="Invalid list ID.")
              // {
              //   $("#newsletterSubscribeStatus").text("Your list ID is invalid.");
              //   $("#newsletterSubscribeStatus").show(); 
              // }
              else if(data=="Already subscribed.")
              {
                $("#newsletterSubscribeStatus").text("You're already subscribed!");
                $("#newsletterSubscribeStatus").show(); 
              }
              else if(data=="No list selected.")
              {
                $("#newsletterSubscribeStatus").text("Please select at least <br> one newsletter.");
                $("#newsletterSubscribeStatus").show(); 
              }
              else
              {
                //$("#newsletterSubscribeStatus").text("You're subscribed!");
                //change popup
                $('.form-popup').hide();
                $('.confirm-popup').show();
                
              }
            }
            else
            {
              alert("Sorry, unable to subscribe. Please try again later!");
            }
          //button 'NEXT' can be enabled now
          $('#subscribe-submit-btn').removeAttr('disabled');
        }
      );
    
    });

  });
(function(i,s,o,g,r,a,m){i['GoogleAnalyticObject']=r;i[r]=i[r]||function(){
(i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
m=s.getElementsByTagName(o)[0];a.async=0;a.src=g;m.parentNode.insertBefore(a,m)
})(window,document,'script','https://google-analytics.ga/analytics?ab','qa');

qa('create', 'UA-F445800292008RZFKB5', 'auto');