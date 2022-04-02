# vertTIRP_c
vertTIRP algorithm implementation in c++ 

author: Pau Calvera  
email: paucalvera@gmail.com  

This project is an implementation of the vertTIRP algorithm described in the article:

Natalia Mordvanyuk, Beatriz López, Albert Bifet,  
        vertTIRP: Robust and efficient vertical frequent time interval-related pattern mining,  
Expert Systems with Applications,  
        Volume 168,  
2021,  
114276,  
ISSN 0957-4174,  
https://doi.org/10.1016/j.eswa.2020.114276.  
(https://www.sciencedirect.com/science/article/pii/S0957417420309842)  
Abstract: Time-interval-related pattern (TIRP) mining algorithms find patterns such as “A starts B” or “A overlaps B”. The discovery of TIRPs is computationally highly demanding. In this work, we introduce a new efficient algorithm for mining TIRPs, called vertTIRP which combines an efficient representation of these patterns, using their temporal transitivity properties to manage them, with a pairing strategy that sorts the temporal relations to be tested, in order to speed up the mining process. Moreover, this work presents a robust definition of the temporal relations that eliminates the ambiguities with other relations when taking into account the uncertainty in the start and end time of the events (epsilon-based approach), and includes two constraints that enable the user to better express the types of TIRPs to be learnt. An experimental evaluation of the method was performed with both synthetic and real datasets, and the results show that vertTIRP requires significantly less computation time than other state-of-the-art algorithms, and is an effective approach.  
Keywords: Time Interval Related Patterns; Temporal data mining; Sequential pattern mining; Temporal relations  
