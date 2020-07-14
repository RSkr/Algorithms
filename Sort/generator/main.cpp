curl --silent -X PUT 'http://localhost:5984/skrodzki/_design/letterssss' -d '
{
    "views":
    {  
        "all":
        {
            "map":
            {
                "function"(doc)
                {

                }
            }

        }
    }
}';