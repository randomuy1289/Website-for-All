document.addEventListener('DOMContentLoaded', function() {
  // Use buttons to toggle between views
  document.querySelector('#inbox').addEventListener('click', () => load_mailbox('inbox'));
  document.querySelector('#sent').addEventListener('click', () => load_mailbox('sent'));
  document.querySelector('#archived').addEventListener('click', () => load_mailbox('archive'));
  document.querySelector('#compose').addEventListener('click', compose_email);

  // By default, load the inbox
  load_mailbox('inbox');
  console.log('')
  document.querySelector('#compose-form').onsubmit = async () => {
          var1 = JSON.stringify({
            recipients: document.querySelector('#compose-recipients').value,
            subject: document.querySelector('#compose-subject').value,
            body: document.querySelector('#compose-body').value
          });
          fetch('emails',{
            method: 'POST',
            body: var1
          })
          .then(response => response.json())
          .then(result => {
              console.log(result);
                });
            load_mailbox('sent');
            return false;
    }

    document.querySelector('#archiveBox').addEventListener('change', () =>{
      email_id = document.querySelector('#emailId').innerHTML;
      if (document.querySelector('#archiveBox').checked == true){
        emailArchive(email_id);
        // load_mailbox('archive');
      }
      else{
        emailUnarchive(email_id);
        // load_mailbox('inbox');
      }
    });
});
function emailOpen() {
  activeView = document.querySelector('#Heading').innerHTML;
  emailView(this.id.slice(2,4) , activeView);
}
function compose_email() {

  // Show compose view and hide other views
  document.querySelector('#emails-view').style.display = 'none';
  document.querySelector('#email-view').style.display = 'none';
  document.querySelector('#compose-view').style.display = 'block';

  // Clear out composition fields
  document.querySelector('#compose-recipients').value = '';
  document.querySelector('#compose-subject').value = '';
  document.querySelector('#compose-body').value = '';

}

function load_mailbox(mailbox) {

  // Show the mailbox and hide other views
  document.querySelector('#emails-view').style.display = 'block';
  document.querySelector('#compose-view').style.display = 'none';
  document.querySelector('#email-view').style.display = 'none';
  // Show the mailbox name
  document.querySelector('#emails-view').innerHTML = `<h3 id="Heading">${mailbox.charAt(0).toUpperCase() + mailbox.slice(1)}</h3>
                                                      <table class="table table-hover"><tbody class='tbody-light' id="emails-table"></tbody></table>`;
  fetch(`emails/${mailbox}`)
  .then(response => response.json())
  .then(result => {
    for (email in result) {
      add_link(result[email], mailbox);
    }
  });

}

 function add_link (content, mailbox) {

   const row = document.createElement('tr');
   row.className = "table-row";
   row.id = `td${content.id}`;
   row.addEventListener('click', emailOpen);
   if (mailbox == 'inbox'){
     row.innerHTML = `<td style="white-space: pre;">${content.sender}             <strong>${content.subject}</strong><p style="float:right;">${content.timestamp}</p></td>`;
   }
   else if (mailbox == 'sent'){
     row.innerHTML = `<td style="white-space: pre;">To:${content.recipients}             <strong>${content.subject}</strong><p style="float:right;">${content.timestamp}</p></td>`;
   }
   else{
     row.innerHTML = `<td style="white-space: pre;">${content.sender}             <strong>${content.subject}</strong><p style="float:right;">${content.timestamp}</p></td>`;
   }
   document.querySelector('#emails-table').append(row);
   if (content.read) {
     document.querySelector(`#td${content.id}`).style.backgroundColor = '#cfcfcf';
   }
 }

function emailView (id, activeView) {
  document.querySelector('#emails-view').style.display = 'none';
  document.querySelector('#compose-view').style.display = 'none';
  document.querySelector('#email-view').style.display = 'block';
  document.querySelector('#archiveMail').style.display = 'none';
  document.querySelector('#compose-reply').style.display = 'none';
  document.querySelector('#emailId').innerHTML = '';
  document.querySelector('#email-recipients').innerHTML = '';
  document.querySelector('#email-sender').innerHTML = '';
  document.querySelector('#email-subject').innerHTML = '';
  document.querySelector('#email-timestamp').innerHTML = '';
  document.querySelector('#email-body').innerHTML = '';
  document.querySelector('#reply-recipient').value = '';
  document.querySelector('#reply-subject').value = '';
  document.querySelector('#reply-body').value = '';
  // console.log(document.querySelector('#Heading').innerHTML);
  fetch(`emails/${id}`, {
    method: 'PUT',
    body : JSON.stringify({
      read: true
    })
  })
  fetch(`emails/${id}`)
  .then(response => response.json())
  .then(result => {
    // console.log(result.read);
    document.querySelector('#emailId').innerHTML = result.id;
    document.querySelector('#email-subject').innerHTML = result.subject;
    if (activeView === 'Sent'){
      document.querySelector('#email-recipients').innerHTML = result.recipients;
      document.querySelector('#archiveMail').style.display = 'none';
    }
    else if (activeView === 'Inbox') {
      document.querySelector('#email-sender').innerHTML = result.sender;
      document.querySelector('#archiveMail').style.display = 'inline-block';
      document.querySelector('#archiveMessage').innerHTML="Archive this mail?";
      document.querySelector('#archiveBox').checked = false;
    }
    else {
      document.querySelector('#email-sender').innerHTML = result.sender;
      document.querySelector('#archiveMail').style.display = 'inline-block';
      document.querySelector('#archiveMessage').innerHTML="Unarchive ?";
      document.querySelector('#archiveBox').checked = true;
    }
    document.querySelector('#email-timestamp').innerHTML = result.timestamp;
    document.querySelector('#email-body').innerHTML = result.body;
  });
}

function reply() {
  document.querySelector('#compose-reply').style.display = 'block';
  replyRecipient = document.querySelector('#email-sender').innerHTML;
  // console.log(replyRecipient);
  document.querySelector('#reply-recipient').value = replyRecipient;
  document.querySelector('#reply-recipient').disabled = true;
  document.querySelector('#reply-subject').value = `Re: ${document.querySelector('#email-subject').innerHTML}`;
  console.log(document.querySelector('#email-subject').innerHTML);
  document.querySelector('#reply-body').value = `On ${document.querySelector('#email-timestamp').innerHTML}, ${replyRecipient} wrote: ${document.querySelector('#email-body').innerHTML} `;
  document.querySelector('#reply-form').onsubmit = async () => {
     var1 = JSON.stringify({
      recipients: replyRecipient,
      subject: document.querySelector('#reply-subject').value,
      body: document.querySelector('#reply-body').value
    });
    fetch('emails',{
      method: 'POST',
      body: var1
    })
    .then(response => response.json())
    .then(result => {
        console.log(result);
        document.querySelector('#compose-reply').style.display = 'none';
        document.querySelector('#reply-recipient').value = '';
        document.querySelector('#reply-subject').value = '';
        document.querySelector('#reply-body').value = '';
        document.querySelector('#reply-recipient').disabled = false;
          });
      return false;
    }
}
function forward(){
  document.querySelector('#compose-reply').style.display = 'block';
  document.querySelector('#reply-recipient').value = '';
  document.querySelector('#reply-recipient').disabled = false;
  replySubject = document.querySelector('#email-subject').innerHTML;
  replyBody = document.querySelector('#email-body').innerHTML;
  document.querySelector('#reply-subject').value = document.querySelector('#email-subject').innerHTML;
  document.querySelector('#reply-body').value = document.querySelector('#email-body').innerHTML;
  document.querySelector('#reply-form').onsubmit = async () => {
     var1 = JSON.stringify({
      recipients: document.querySelector('#reply-recipient').value,
      subject: document.querySelector('#reply-subject').value,
      body: document.querySelector('#reply-body').value
    });
    fetch('emails',{
      method: 'POST',
      body: var1
    })
    .then(response => response.json())
    .then(result => {
        console.log(result);
        document.querySelector('#compose-reply').style.display = 'none';
        document.querySelector('#reply-recipient').value = '';
        document.querySelector('#reply-subject').value = '';
        document.querySelector('#reply-body').value = '';
          });
      return false;
    }
}
function emailArchive(email_id){
  fetch(`emails/${email_id}`, {
    method: 'PUT',
    body : JSON.stringify({
      archived: true
    })
  })
  .then(result => {
    load_mailbox('archive');
  })
}
function emailUnarchive(email_id){
  fetch(`emails/${email_id}`, {
    method: 'PUT',
    body : JSON.stringify({
      archived: false
    })
  })
  .then(result => {
    load_mailbox('inbox');
  })
}
