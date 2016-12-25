public interface HuffmanInterface
{
	/**
	 * This method will be called to generate your tree.  The return type is void because this method simply creates the 
	 * tree.  The other methods will be used to encode or decode the text
	 * 
	 * @param sampleTest The sample text to be used when generating the tree
	 */
	public void  createTree(String sampleText);
	
	
	
	/**
	 * This method is called to encode a Beeoeyehuish message into 1s and 0s using the tree that was created when the 
	 * createTree method was called.
	 * 
	 * @param message The message to be encoded
	 * 
	 * @return The encoded message
	 */
	public String encodeMessage(String message);
	
	
	
	/**
	 * This method is called to decode a message of 1s and 0s back into Beeoeyehuish using the tree that was created when 
	 * the createTree method was called.
	 * 
	 * @param encodedMessage The encoded message (1s and 0s) to be decoded
	 * 
	 * @return The decoded message
	 */
	public String decodeMessage(String encodedMessage);
	
}