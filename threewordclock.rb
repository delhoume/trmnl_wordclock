# three word clock by delhoume@gmail.com    this code is free
module Plugins    
  #class ThreeWordClock < Base

    def locals = { utc_offset:    }


    private
      now = Time.now
      utc_offset = 0 #now.utc_offset * 60 * 1000 
      trmnl_user_offset = 0 #-28800 * 1000  # user plugin parameter ? (in seconds)
      now = Time.at(now.to_i + trmnl_user_offset + utc_offset)

      hour = now.hour
      minutes = now.min
      num_five = (minutes / 5).floor()
      displayed_hour = minutes > 30 ? hour + 1 : hour;
      word_three_map = ["MIDNIGHT", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX",
          "SEVEN", "EIGHT", "NINE", "TEN", "ELEVEN", "NOON"]

      word_one_map = [
          ["FIVE", "PAST"], ["TEN","PAST"], ["QUARTER", "PAST"], ["TWENTY", "PAST"],
          ["TWENTY-FIVE",  "PAST"], ["HALF",  "PAST"], ["TWENTY-FIVE", "TO"],
          ["TWENTY", "TO"], ["QUARTER", "TO"], ["TEN", "TO"], ["FIVE",  "TO"]
      ]

      word_one = "\u00a0"
      word_two = "\u00a0"
      word_three = word_three_map[displayed_hour % 12]
          
      if num_five == 0 
            if hour == 0 || hour == 12
              word_two = word_three
              word_three = "\u00a0"
            else
              word_one = word_three
              word_three = "O'CLOCK"
              word_two ="\u00a0" 
            end
      else 
            word_one = word_one_map[num_five - 1][0]
            word_two = word_one_map[num_five - 1][1]
      end

      print word_one
      print word_two
      print word_three

end