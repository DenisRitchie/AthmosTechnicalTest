# Too many tasks, not enough speed

In the company is developing a system that is responsible for sending different reports (emails) to
many recipients, then there is a problem that for each sending - it takes time to get the mails out and if
one of the mails presents a problem the sending queue is broken - then the company is looking for
you to be able to develop a system that can run these mails keeping in mind that your solution must
solve the following points:

__Tasks:__ <br/>
* Mails must now be processed separately and in parallel.
  * Mail pending processing
  * Mails under retry process
  * Priority mails

* Get each mail queue (pending, retry, priority) to run in different processes, each queue
  processing process should run the same in N number of defined sub processes (recommended 8 sub processes).

* When the script finishes it must execute certain tasks:
  * Saving process of a .txt file with the information or report of the sent emails, where
    information such as: id, number of attempts, if it is a priority or not, example: `101, 6, true`

* Show in console how long it took (in seconds) to process all the mails (from all the queues).

* Save a graph in .jpeg format representing the following information.
  * Number of emails executed per 0.5 seconds.
  * Number of failed emails per 0.5 seconds.
  * Number of new emails added to the queue per 0.5 seconds.

__The following is the code that has the described problem:__ <br/>
* Python: https://bitbucket.org/creed-and-bear/recruiting-test-python-01/src/master/

__Remember:__ <br/>
You should refactor the actual code, you should not change the methods that are marked.
