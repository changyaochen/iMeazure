modified by changyao chen  


from 9/2014, the latest update is added to the top of this document.

3/23/15
another try to make CH2 downward megasweep available... not work yet...
 
3/4/15
Realized that the saving only conserve 6 significant numbers, that's not enough for very stable frequency output!


2/13/15
going to modify the megaweep settings so that, I can take data with ch2 stespping down.....
not finished yet... the work will be carried out in v92

12/2/14
change the unit of E4402B from Mhz to kHz

11/26/14
transfer the LabWindows/CVI to Lab PC (bohium), it will easier to debug while the instruments are physically connected.
will working on put SIM 965 analog filters into iMeazure, DONE, add 2 SIM965s

11/17/14
received the DAQ system from NI, going to activate the DAQ functionalities in iMeazure, not done

11/5/14
shorten the x_axis list, only includes the first 10 items.
going to add SIM965 into iMeazure. - not finished/tested

11/4/14
will srcap the Zi plan for now, but will add SR850 amplitude control into the software. Done.

10/31/14
rename the version to v91
going to add Zuirch Instrument Lock-in(s) into the system. The communication will be USB, not GPIB...
Copied head files from the Zi's files
will start from acquiring X and Y data..., working progress...

10/21/14
fixed the problem in change_chx.type problem, added proper "return 0;" in each if statement.

10/3/14
fixed the megasweep problem that, when both (ch1) up/down sweep are selected to be saved, ch2 will step between the up/down sweep. 

10/3/14
going to add the frequency source, Agilent 33220A, for both frequency and amplitude control
DONE!

9/25/14
Will look into why megasweep can only save y and y1, but not y2. 
It was not designed to save y2 data in megasweep. Added such function now.

9/24/14
Trying to put Zurich Instrument UHF lock-in into iMeazure. Got the C expamle code from Dave/Company.
Installed required driver to the PC. 
It doesn't seem to be an urgent task now, will put it off.


9/22/14
going to check the number format problem in megasweep. change the data type from float (%f) to scientfic (%e). Should solve this problem. Yes, problem solved.

9/18/14
going to add the AUX output of SR lock-ins into iMeazure, as voltage source. DONE!

9/15/14
Fixed the SR850 initializatio problem (set "sweep_ch1.x" to a resonable value).
Will try to put Keithley 2000 DMM into the software.
Keithley 2000 is already in there (GPIB = 16)! Thanks Kirill!

9/12/14
Fix the codes so that it will run in x64 environment, got it running in Windows 8.1;
Going to add SR850 into the system, which is both a lock in and sweep-able frequency source;
Will dub this equipment with previous SR844, which in the code is treated as SR830_2. Therefore, still share the GPIB address of 8; 
Able to read SR850, both X and Y!
Working on sweeping the SR850, again under the alias of SR830_2, almost done, need to work on the initialization function.

9/29/10

add Agilent VNA E5062, also integrated megasweep w/ E5062



10/5/10

corrected PPMS sweep

7/11/11
added all the 4 SIM928's, solved the overflow problem by resetting the module every 5 minutes



8/5/11

trying to add SIM970 4 channel DVM 

8/16/11
add first SIM970 channel, but very noisy, will debug...



8/25/11

add all the SIM970 channels, but have problem while acquiring more than 1 SIM970 in y, probably some buffer problem, will look later



8/29/11

trying to add Agilent ESA E4402B, maybe mega too?
as of 3:30pm, finished machine setting functions change, will be on to integrate to panel



9/14/11

continue working on E4402B, finished single sweep, will work on mega in a bit
maybe put on graphing?



9/15/11

put in E4402B mega, done!
E4402B graphing done! hopefully works for E5062 too...



12/26/11

fixed E5062/E4402 mega first data set x-column problem. 



3/7/12

will try to integrate the DAQ from v80
done! test DAC out, works fine, yet to test DAC in later..



3/9/12

put in HP53132A frequency counter, with tha alias of HP34401#2, i.e. only the command is changed 



3/12/12

optimized the throughput for HP34401A and HP53132A



3/13/12

fixed the YOKO problem!



8/15/12

going to add 3rd channel for megasweep...
added the 3rd channel OK! now need to add in megasweep capability...



8/16/12

going to add 3rd channel into E5602A mega, i.e., step both CH 2 & 3 after each CH1 sweep.



8/19/12

add 3rd channel into regular mega!! working on saving data problem, struggling...



8/20/12

found out the stupid mistake... && is AND operatore, while || is OR operator!! making progress now...
tested regular megasweep, working!! now taking a break while Adam using the tool, will come back for E5062 and E4402 3rd channel mega..
working on it!! seems pretty easy, just copy & paste..... yet to field test...
done! 


