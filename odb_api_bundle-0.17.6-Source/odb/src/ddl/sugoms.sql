SET $tslot = -1;

READONLY;

CREATE VIEW sugoms AS
  SELECT seqno, // for debugging purposes only
         timeslot@index, obstype, 
	       mapomm,
    FROM timeslot_index, index, hdr
   WHERE ($tslot == -1 AND timeslot@timeslot_index > 0) OR (timeslot@timeslot_index == $tslot)
 ORDERBY mapomm
;
