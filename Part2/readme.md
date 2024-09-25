# Part 2: Trading Specific Algorithms

### Data Retrieval and Processing:
Instead of treating the data as a complete download, I chose to process each chunk as it arrives. Using cURL, the program connects to the API and downloads the data in chunks, storing them in a buffer. Each chunk is processed as soon as it is received, and incomplete JSON objects at the end of the chunk are removed to ensure valid data. This way, the program can handle incoming trades in real-time without waiting for the entire dataset.

### Parsing and Trade Structure:
I decided to use a `Trade` struct instead of working directly with the parsed JSON data for better structure and readability, making it easier to work with the individual trade elements. Each trade is parsed from the JSON data into a `Trade` struct and printed with its relevant details. The time taken to parse each trade is measured and displayed. Additionally, I chose to use **`int64_t`** for the trade ID fields instead of **`int`** or **`long`**. This is because **`int`** cannot handle the large values of trade IDs, and **`long`** is system-specific, which could cause portability issues. **`int64_t`** ensures consistent behavior across different platforms with a fixed-size integer.

### Chunk Handling:
To handle incomplete data at the end of each chunk, I implemented the `trim_incomplete_json()` function. This ensures that only valid, complete JSON objects are processed, allowing the program to continue without errors when a new chunk arrives. By doing this, I made sure that real-time processing remains uninterrupted.

### Complexity and Performance:
The `parse_trades()` function operates with O(N) complexity, where N is the size of the JSON data in each chunk. This decision helps maintain efficient processing, even with large incoming data streams. I also added extra counters to measure the total running time and total parsing time, even though the original request only required individual parsing times. I thought this would provide additional insight into the program's overall performance.

### Error Handling:
While the program includes basic error handling for API errors and JSON parsing issues, I believe there is room for improvement. Currently, any errors encountered during data retrieval or parsing are logged with a timestamp, and the program continues processing the next chunk. However, more sophisticated error-handling mechanisms could be added to enhance robustness, such as better recovery options and detailed error reporting.

### Counters and Timing:
As mentioned, I implemented additional counters to measure not only the time taken for each trade's parsing but also the total time spent parsing all trades and the overall running time of the program. This was an extra feature I chose to include for performance analysis, though the original task only required the timing of individual trades.
